#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, cli_addr;
    char buf[100];
    int cli_len;

    if(sockFD < 0){
        printf("Socket creation failed\n");
        return 0;
    } else {
        printf("Socket creation successful\n");
    }

    //server properties
    server_addr.sin_family = AF_INET; //protocol type: ipv4
    server_addr.sin_addr.s_addr = INADDR_ANY; //addr of server: unknown
    server_addr.sin_port = 4000; //port number

    //bind
    if(bind(sockFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("Local address bind failed\n");
        exit(0);
    }else{
        printf("Local address bind successful\n");
    }

    //listen
    if(listen(sockFD,5) < 0){
        printf("Server is not listening");
    }else{
        printf("Server is not listening");
    }
    
    //accept requests
    cli_len = sizeof(cli_addr);
    int newSockFD = accept(sockFD, (struct sockaddr *)&cli_addr, &cli_len);
    if(newSockFD < 0){
        printf("Request denied");
        exit(0);
    }else{
        printf("Request accepted");
    }
    if(fork() == 0){
        close(sockFD);
        for(int i = 0; i < 100; i++){
            buf[i] = '\0';
        }
        
        //send
        strcpy(buf, "Message from server");
        
        send(newSockFD, buf, 100, 0);
        for(int i = 0; i < 100; i++){
            buf[i] = '\0';
        }

        //receive
        recv(newSockFD, buf, 100, 0);
        printf("%s\n", buf);
        close(newSockFD);
        exit(0);
    }
    close(newSockFD);

    return 0;
}
