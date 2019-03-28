#include "socket.h"
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

using namespace std;

Socket::Socket(int port,const char* ip_addr)
{
    sockfd = 0;
    addr = new sockaddr_in[sizeof(sockaddr_in)];
    try{
        createSocket();
        initSocket(port,ip_addr);
        linkSocket();
    }catch (const char* ex){
        throw ex;
    }
}

Socket::~Socket()
{
    delete addr;
    if(sockfd>0)close(sockfd);
}

//接收
int Socket::recvMsg(void)
{
    char buf[4096] = {};
    int ret = recv(sockfd,buf,sizeof(buf),0);
    if(ret < 0)
    {
        perror("recv");
        return -1;
    }
    qDebug() << buf;
    return ret;
}

int Socket::recvMsg(string& buf)
{
    char recvbuf[4096] = {};
    int ret = recv(sockfd,recvbuf,sizeof(recvbuf),0);
    if(ret < 0)
    {
        perror("recv");
        return -1;
    }
    buf.append(recvbuf);
    return ret;
}
//发送
void Socket::sendMsg(const char* command,const char* content)
{
    char buf[4096] = {};
    sprintf(buf,command,content);
    qDebug() << buf;
    send(sockfd,buf,strlen(buf),0);
}

void Socket::sendMsg(const char* command)
{
    char buf[4096] = {};
    sprintf(buf,command,"");
    qDebug() << buf;
    send(sockfd,buf,strlen(buf),0);
}

int Socket::sendMsg(const string& buf)
{
    int ret = send(sockfd,buf.c_str(),buf.size(),0);
    if(ret < 0)
    {
        perror("send");
        return ret;
    }
    return ret;
}

//连接
void Socket::linkSocket(void)
{
    int ret = connect(sockfd,(struct sockaddr*)addr,sizeof(struct sockaddr_in));
    if(ret < 0)
    {
        perror("connect");
        throw "连接失败";
    }
}

//准备IP地址
void Socket::initSocket(int port,const char* ip_addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = inet_addr(ip_addr);
}

//创建socket对象
void Socket::createSocket(void)
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd <= 0)
    {
        perror("socket");
        throw "socket创建失败";
    }
}
