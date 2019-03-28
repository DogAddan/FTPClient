#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <arpa/inet.h>
#include <QtDebug>

using namespace std;

class Socket
{
public:
    //构造
    Socket(int port,const char* ip_addr);
    //析构
    ~Socket(void);
    //发送
    void sendMsg(const char* command,const char* content);
    void sendMsg(const char* command);
    int sendMsg(const string& buf);
    //接收
    int recvMsg(void);
    int recvMsg(string& buf);
private:
    //套接字描述符
    int sockfd;
    //目标地址
    sockaddr_in* addr;

    //创建socket对象
    void createSocket(void);
    //准备IP地址
    void initSocket(int port,const char* ip_addr);
    //连接
    void linkSocket(void);
};

#endif // SOCKET_H
