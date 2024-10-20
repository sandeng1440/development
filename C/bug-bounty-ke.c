#include "pcap.h"

#define EXPAND_IP_32(ipp) ((__u8*)(ipp))[0], ((__u8*)(ipp))[1], ((__u8*)(ipp))[2], ((__u8*)(ipp))[3]
#define likely(x)    __builtin_expect (!!(x), 1)

int open_pcap(struct f_pcap *p)
{
    p->file = pcap_open_offline(p->pcap_filename, p->errbuf);
    if(!p->file) {
        printf("Failed to open pcap file: %s\n", p->errbuf);
        return -1;
    }
    return 0;
}

int open_pcap_live(struct f_pcap *p)
{
    p->file = pcap_open_live(p->pcap_interface, 4096000, 1, 100, p->errbuf);
    if(!p->file) {
        printf("Failed to open interface %s for packet capture: %s\n", p->pcap_interface, p->errbuf);
        return -1;
    }
    return 0;
}
/** hex_pdump_buffer prints a wireshark parseable hex dump from a specified pointer
 * @param buffer - Pointer to the memory location to be dumped
 * @param size - The size of the data that will be printed
 */
void hex_dump_ptr(void *buffer,__u16 size)
{
    char ret_print[18];
    void *cur_pkt = buffer;
    printf ("%06x\t",0);
    fflush (stdout);
    for(int p = 0; p < size; p++)
    {
        if((p + 1) % 16 == 0)
            snprintf (ret_print,10,"\n%06x\t",p + 1);
        printf ("%02x%s",*(uint8_t *) (cur_pkt + p),
                ((p + 1) % 16 == 0)?ret_print:" ");
        fflush (stdout);
    }
    printf ("\n\n");
    fflush (stdout);
}


void callback(u_char *c, const struct pcap_pkthdr* pkthdr, const u_char *packet)
{
    __u16 ptype = ntohs(*(__u16*)(packet+12));
    __u8 version;
    struct f_pcap *fp  = (struct f_pcap *)c;
    fp->counter++;
    switch(ptype) {
        case 0x0800:
            packet += 14;
            fp->total_packets++;
            break;
        case 0x8100:
            packet += 18;
            fp->vlan_packets++;
            fp->total_packets++;
            break;
        case 0x86DD:
            fp->ipv6_packets++;
            fp->ipv6_data += pkthdr->caplen;
            return;
        case 0x8847: // Skip MPLS Packets
        case 0x88CC: // Skip LLDP Packets
        case 0x8809: // Skip Link Aggregation packets
        case 0x0806: // Skip ARP Packets
        default:
            return;
    }
    version = (*packet)>>4;
    if(likely(version == 4)) {
        packet+=12;
        __u32 src_address = *(__u32*)(packet);
        __u32 dst_address = *(__u32 *)(packet+4);
        dst_address &= 0x00ffffff;
        src_address &= 0x00ffffff;
        if(fp->account_dst[dst_address] == NULL)
            if((fp->account_dst[dst_address] = calloc(1, sizeof(struct accounting))) == NULL) {
                printf("Failed allocating memory for counters\n");
                return;
            }
        if(fp->account_src[src_address] == NULL)
            if((fp->account_src[src_address] = calloc(1, sizeof(struct accounting))) == NULL) {
            printf("Failed allocating memory for counters\n");
            return;
        }
        //printf("Using destination address %u.%u.%u.%u at offset %p\n",
        //    EXPAND_IP_32(&dst_address), fp->account_dst[dst_address]);
        //printf("Using source address %u.%u.%u.%u at offset %p\n",
        //       EXPAND_IP_32(&src_address), fp->account_src[src_address]);
        fp->account_dst[dst_address]->data_count += pkthdr->caplen;
        fp->account_dst[dst_address]->prefix = dst_address;
        fp->account_dst[dst_address]->packet_count++;
        fp->account_src[src_address]->data_count += pkthdr->caplen;
        fp->account_src[src_address]->prefix = dst_address;
        fp->account_src[src_address]->packet_count++;
        fp->total_data += pkthdr->caplen;
    }
    if(fp->counter % 10000000 == 0) {
        printf("Processed %llu packets\r", fp->counter);
        fflush(stdout);
    }
    if(fp->counter >= 1000000000) {
                pcap_breakloop(fp->file);
    }
}

int main() {
    struct f_pcap p = {0};
    p.counter = 0;
    p.account_src = calloc(16777216, sizeof(struct accounting *));
    p.account_dst = calloc(16777216, sizeof(struct accounting *));
    p.total_data = 0;
    FILE *csv_output_dst = fopen("dst.csv", "w");
    FILE *csv_output_src = fopen("src.csv", "w");
    if(p.account_src == NULL) {
        printf("Failed to allocate for accounting structure\n");
        return -1;
    }
    if(p.account_dst == NULL) {
        printf("Failed to allocate for accounting structure\n");
        return -1;
    }
    for(int i = 0; i < 16777216; i++) {
        p.account_src[i] = NULL;
        p.account_dst[i] = NULL;
    }
    //snprintf(p.pcap_filename, 1024, "enp5s0.pcap");
    snprintf(p.pcap_interface, 1024, "enp5s0");
    if(open_pcap_live(&p)) {
        printf("Failed opening pcap file\n");
        return -1;
    } else {
        printf("Opened pcap interface %s successfully\n", p.pcap_interface);
    }
    printf("\n");
    pcap_loop(p.file, 0, callback, (u_char*)&p);
    printf("\n");
    pcap_close(p.file);
    p.file = NULL;
    p.counter = 0;
    //snprintf(p.pcap_filename, 1024, "enp133s0.pcap");
    snprintf(p.pcap_interface, 1024, "enp133s0");
    if(open_pcap_live(&p)) {
        printf("Failed opening pcap file\n");
        return -1;
    } else {
        printf("Opened pcap interface %s successfully\n", p.pcap_interface);
    }
    printf("\n");
    pcap_loop(p.file, 0, callback, (u_char*)&p);
    printf("\n");
    pcap_close(p.file);
    for(__u32 i = 0; i < 16777216; i++) {
        if(p.account_src[i] != NULL) {
            if(p.account_src[i]->packet_count < 255)
                continue;
            fprintf(csv_output_src, "%u.%u.%u.%u,%llu,%llu\n", EXPAND_IP_32(&i),
                    p.account_src[i]->data_count, p.account_src[i]->packet_count);
        }
        if(p.account_dst[i] != NULL) {
            if(p.account_dst[i]->packet_count < 255)
                continue;
            fprintf(csv_output_dst, "%u.%u.%u.%u,%llu,%llu\n", EXPAND_IP_32(&i),
                    p.account_dst[i]->data_count, p.account_dst[i]->packet_count);
        }
    }
    fclose(csv_output_dst);
    fclose(csv_output_src);
    printf("Found %llu vlan packets (out of %llu packets)\n", p.vlan_packets, p.total_packets);
    printf("Found %llu ipv6 packets containing %llu bytes of data\n", p.ipv6_packets, p.ipv6_data);
}
