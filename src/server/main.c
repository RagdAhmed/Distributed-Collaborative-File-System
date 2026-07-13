#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>
#include <unistd.h>    
#include <arpa/inet.h> 
#include <sys/socket.h>

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
    server_addr.sin_port = htons(8432);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(1);
    }


    printf("Bound to port 8080\n");
    return 0;
}