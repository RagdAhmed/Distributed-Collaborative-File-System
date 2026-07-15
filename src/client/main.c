#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>
#include <unistd.h>    
#include <arpa/inet.h> 
#include <sys/socket.h>
#include "../../include/protocol.h"
#include "../../include/net_utils.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("usage: %s <server ip> <port>\n", argv[0]);
        exit(1);
    }
    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0 ,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // converting loopback ip into binary 
    if (inet_pton(AF_INET, server_ip , &server_addr.sin_addr) <= 0) {
        perror("invalid address");
        exit(1);
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(1);
    }
    
    printf("Connected to server\n");

    MessageHeader header;
    header.command = CMD_UPLOAD;
    header.filename_len = 0;
    header.payload_len = 0;

    if(send_all(sock_fd, &header, sizeof(header)) < 0){
        perror("failed to send header");
        exit(1);
    }
    printf("Header sent: command=%u\n", header.command);
    close(sock_fd);
    return 0;
}