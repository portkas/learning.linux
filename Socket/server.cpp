#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>

const int PORT = 27015;

int main(){
    // 创建监听的套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(0);
    }

    // 绑定本机IP端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1){
        perror("bind");
        exit(0);
    }

    // 开始监听
    ret = listen(lfd, 100);
    if(ret == -1){
        perror("listen");
        exit(0);
    }

    // 建立连接
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
    if(cfd == -1){
        perror("accept");
        exit(0);
    }
    char ip[24] = {0};
    printf("Windows IP:%s, Port:%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)), ntohs(cliaddr.sin_port));

    // 数据传输
    while(1){
        char buf[1024];
        char answer[4] = "ok";
        memset(buf, 0, sizeof(buf));
        int len = recv(cfd, buf, sizeof(buf), 0);
        if(len > 0){
            printf("Windows say:%s\n", buf);
            send(cfd, answer, sizeof(answer), 0);

            std::vector<char*> parts;
            char* token = strtok(buf, " ");
            while(token != nullptr){
                parts.push_back(token);
                token = strtok(nullptr, " ");
            }
            if (parts.size() >= 2) {
                if (strcmp(parts[0], "read") == 0) {
                    if (strcmp(parts[1], "exposure") == 0) {
                        printf("执行--读取相机曝光函数--\n");
                    } else if (strcmp(parts[1], "led") == 0) {
                        printf("执行--读取投影仪led电流值函数--\n");
                    } else {
                        printf("读取错误，请重新读取\n");
                    }
                } else if (strcmp(parts[0], "set") == 0) {
                    if (parts.size() >= 3) {
                        if (strcmp(parts[1], "exposure") == 0) {
                            printf("曝光时间被设置为：%d\n", std::stoi(parts[2]));
                        } else if (strcmp(parts[1], "led") == 0) {
                            printf("led电流值被设置为：%d\n", std::stoi(parts[2]));
                        } else {
                            printf("设置错误，请重新设置\n");
                        }
                    } else {
                        printf("缺少设定值\n");
                    }
                }
            } else {
                printf("命令格式错误\n");
            }
        }else if(len == 0){
            printf("Windows break...\n");
            break;
        }else{
            perror("read");
            break;
        }
    }

    // 关闭
    close(cfd);
    close(lfd);
    return 0;
}