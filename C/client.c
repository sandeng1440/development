#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct sockaddr_in server_addr;
  uint32_t sockFD = socket(AF_INET, SOCK_STREAM, 0);
  char buf[100];

  if (sockFD < 0) {
    printf("Socket creation failed\n");
    return 0;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = 4000;

  if (connect(sockFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    printf("Unable to connect to server\n");
    return 0;
  } else {
    printf("Connected to server successfully\n");
  }

  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }
  recv(sockFD, buf, 100, 0);
  printf("%s\n", buf);
  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }
  close(sockFD);

  return 0;
}
