#ifndef FTP_H
#define FTP_H

#include "socket.h"

class FTP
{
private:
    Socket* socketSend;
    Socket* socketRecv;

    //连接服务器
    void linkServer(void);
    //获取新端口
    void getNewPort(void);
    //pwd
    void getPWD(string&);
public:
    //构造
	FTP(int port,const char* ip_addr);
	//析构
    ~FTP(void);
	//ls
    void commandLs(string& str);
	//cd
    void commandCd(const string& command);
    void commandCd(const string& command,string& str);
	//get
    void commandGet(const string& commandStr);
	//put
    void commandPut(const string& commandStr);
    void commandPut(const string& filePath,const string& fileName);
	//bye
	void commandBye(void);

};


#endif // FTP_H
