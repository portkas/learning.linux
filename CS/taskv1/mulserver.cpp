#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 25500


void* socketConn(void *arg){
    
}

int main(){
    // 创建监听套接字socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout<<"sockfd: "<<sockfd<<std::endl;
    if(sockfd == -1){
        perror("socket");
        exit(0);
    }

    // 绑定本地IP和端口bind
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(sockfd, (sockaddr*)&addr, sizeof(addr));
    if(ret == -1){
        perror("bind");
        exit(0);
    }

    // 设置监听listen
    ret = listen(sockfd, 128);
    if(ret == -1){
        perror("listen");
        exit(0);
    }

    // 建立连接
    socklen_t addrlen = sizeof(addr);
    int cfd = accept(sockfd, (sockaddr*)&addr, &addrlen);
    std::cout<<"cfd: "<<cfd<<std::endl;
    if(cfd == -1){
        perror("accept");
        exit(0);
    }else{
        char buffer[1024];
        while(1){
            memset(buffer, 0, sizeof(buffer));
            ssize_t len = read(cfd, buffer, sizeof(buffer));
            if(len < 0){
                perror("read");
                exit(0);
            }else if(len == 0){
                std::cout<<"客户端断开连接...."<<std::endl;
                break;
            }else{
                for(int i=0; i<len; ++i){
                    if(buffer[i] >= 'a' && buffer[i] <= 'z') {
                        buffer[i] -= 'a' - 'A';
                    }
                }
                write(cfd, buffer, len);
            }
        }
    }
    ret = close(sockfd);
    ret = close(cfd);
    if(ret == -1){
        perror("close");
        exit(0);
    }
    return 0;
}