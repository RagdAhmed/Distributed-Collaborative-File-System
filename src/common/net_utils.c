#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>
#include <unistd.h>    
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <stddef.h>

//makes sure whole message is sent/recieved by looping and checking byte size
int send_all (int sockfd, const void *buf, size_t len) {
    size_t total = 0;
    const char *data = (const char *)buf;

    while (total < len) {
        ssize_t sent = send(sockfd, data + total, len - total, 0);
        if(sent <= 0) {
            return -1;
        }
        total += sent;
    }
    return 0;
}

int recv_all(int sockfd, void *buf, size_t len) {
    size_t total = 0;
    char *data = (char *)buf;

    while (total < len) {
        ssize_t rec = recv(sockfd, data + total, len - total, 0);
        if(rec <= 0) {
            return -1;
        }
        total += rec;
    }
    return 0;
}