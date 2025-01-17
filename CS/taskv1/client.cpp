#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 25500
#define serverIP "49.123.87.90"

int main(){
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1){
        perror("socket");
        exit(0);
    }

    int ret;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ret = inet_pton(AF_INET, serverIP, &addr.sin_addr.s_addr);
    ret = connect(cfd, (sockaddr*)&addr, sizeof(addr));
    if (ret == -1) {
        perror("connect");
        exit(0);
    }

    int i=0;
    while(1)
    {
        char sendbuffer[1024];
        char recvbuffer[1024];
        sprintf(sendbuffer, "data: %d\n", i++);
        write(cfd, sendbuffer, strlen(sendbuffer)+1);
        read(cfd, recvbuffer, sizeof(recvbuffer));
        printf("send buf: %s", sendbuffer);
        printf("recv buf: %s\n", recvbuffer);
        sleep(1);
    }

    ret = close(cfd);
    if(ret == -1){
        perror("close");
        exit(0);
    }
    return 0;
}