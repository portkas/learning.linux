---
title: socket
categories:
	- 套接字通讯
---
# 多客户端通讯问题

* 多线程
* 多进程
* IO转接+多线程
* libevent

<!-- more -->

# 概念

* 局域网IP：标识主机
* 广域网IP：标识主机
* 端口（16位）：标识进程

# 网络协议

```bash
# Linux
$ ifconfig

# Windows
$ ipconfig

# 测试网络
$ ping www.baidu.com
```

# socket编程

* 客户端，服务器端
* IP，端口，通信数据

# 字节序

* 大端（网络字节序）：低位字节存储在内存的高地址位（从高到低读即从左往右读）
* 小端（主机字节序）：低位字节存储在内存的低地址位（从低到高读即从右往左读）
* 函数：ntohs(), ntohl(), htons(), htonl()
  * 头文件：#include < arpa/inet.h >
  * htons(),htonl()：主机字节序转网络字节序
  * ntohs(),ntohl()：网络字节序转主机字节序

# IP地址转换

主机字节序的IP地址是字符串，网络字节序IP地址是整型

## inet_pton()

主机

```c
int inet_pton(int af, const char *src, void *dst)
```
