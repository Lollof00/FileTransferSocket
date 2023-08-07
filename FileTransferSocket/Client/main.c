#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024

void send_file(FILE *fp, int sockfd){
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp) != NULL){
        if(send(sockfd, data, sizeof(data), 0) == -1){
            perror("[-]Error in sending data.\n");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main() {

    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "file1.txt";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("[-]Error in socket.");
        exit(1);
    }
    printf("[+]Server socket create.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1){
        perror("[-]Error connecting.\n");
        exit(1);
    }else{
        printf("[+]Connected to server.\n");
    }

    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("[-]Error reading file.\n");
        exit(1);
    }

    send_file(fp, sockfd);
    printf("[+]File data send successfully.\n");
    close(sockfd);
    printf("[+]Disconnected from the server.\n");

    return 0;
}
