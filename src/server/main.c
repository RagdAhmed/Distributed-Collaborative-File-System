#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>
#include <unistd.h>    
#include <arpa/inet.h> 
#include <sys/socket.h>
#include "../../include/protocol.h"
#include "../../include/net_utils.h"

int main() {
    //creating the socket
    int server_fd = socket(AF_INET,  SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    //binding socket to port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 ,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }
    printf("Bound to port 8080\n");

    //listens for and accepts connections
    if(listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(1);       
    }
    printf("listening on port 8080\n");

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if(client_fd < 0) {
        perror("accept failed");
        exit(1);
    }

    printf("client connected.\n");
    
    MessageHeader header;
    if(recv_all(client_fd, &header, sizeof(header)) < 0) {
        perror("failed to receive header");
        exit(1);
    }
    printf("Received header: command=%u, filename_len=%u, payload_len=%lu\n", header.command, header.filename_len, header.payload_len);
    
    return 0;
}  