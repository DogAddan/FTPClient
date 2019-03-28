#include "FTP.h"
#include <iostream>
#include <fstream>

#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

using namespace std;

//连接FTP服务器
void FTP::linkServer(void)
{
	//发送用户名
	socketSend->sendMsg("USER %s\n","EOS1811");
    //接收
	socketSend->recvMsg();
	//发送密码
	socketSend->sendMsg("PASS %s\n","ooss1811");
    //接收
	socketSend->recvMsg();
}
//获取新端口
void FTP::getNewPort(void)
{
    //PASV
    socketSend->sendMsg("PASV\n");
    //接收新的端口号
    string str;
	socketSend->recvMsg(str);
	//解析端口号
	unsigned char port1,port2;
	sscanf(str.c_str(),"227 Entering Passive Mode (%*d,%*d,%*d,%*d,%hhu,%hhu)",&port1,&port2);
	short port = port1*256+port2;
    qDebug("正在打开数据连接 IP: 192.168.6.66 端口: %hd\n",port);
    //连接新端口
    delete socketRecv;
    try{
        socketRecv = new Socket(port,"192.168.6.66");
    }catch(const char* ex){
        throw ex;
    }
}
//执行ls命令
void FTP::commandLs(string& str)
{
    //获取新端口
    try{
        getNewPort();
    }catch(const char* ex){
        throw ex;
    }
    //发送LIST命令
    socketSend->sendMsg("LIST -al\n");
    //接收
    socketSend->recvMsg();
    //接收
    socketSend->recvMsg();
    //接收文件信息
    str.clear();
    while(socketRecv->recvMsg(str)>0);
}
//cd
void FTP::commandCd(const string &commandStr)
{
    //提取文件路径
    char temp[1024] = {};
    sscanf(commandStr.c_str(),"cd %s",temp);
    //CWD命令
    socketSend->sendMsg("CWD %s\n",temp);
    //接收
	socketSend->recvMsg();
    //PWD命令
    socketSend->sendMsg("PWD\n");
    //接收
    socketSend->recvMsg();
}
//cd
void FTP::commandCd(const string &commandStr,string& str)
{
    //提取文件路径
    char temp[1024] = {};
    sscanf(commandStr.c_str(),"cd %s",temp);
    //CWD命令
    socketSend->sendMsg("CWD %s\n",temp);
    //接收
    socketSend->recvMsg();
    //PWD命令
    getPWD(str);
}
//pwd
void FTP::getPWD(string& str)
{
    //PWD命令
    socketSend->sendMsg("PWD\n");
    //接收
    socketSend->recvMsg(str);
    qDebug() << str.c_str();
    str.erase(0,5);
    str.resize(str.size()-3);
}

//get
void FTP::commandGet(const string& commandStr)
{
    //提取文件路径
    char temp[1024] = {};
    sscanf(commandStr.c_str(),"get %s",temp);
    //TYPE命令
	socketSend->sendMsg("TYPE I\n");
    //接收
	socketSend->recvMsg();
    string str;
    //SIZE命令
    socketSend->sendMsg("SIZE %s\n",temp);
    //接收
	socketSend->recvMsg(str);
	cout << str;
	if(0 == str.find("550"))return;
    //MDTM命令
    socketSend->sendMsg("MDTM %s\n",temp);
    //接收
    str.clear();
    socketSend->recvMsg(str);
    cout << str;
//    char *time = str.c_str();
//   int year,month,day,hour,min,sec;
    //获取新端口
    try{
        getNewPort();
    }catch(const char* ex){
        throw ex;
    }
    //RETR命令
    socketSend->sendMsg("RETR %s\n",temp);
    //接收文件
    str.clear();
	while(socketRecv->recvMsg(str) > 0);
    //写文件
    ofstream ofs (temp,ios::out);
    ofs.write(str.c_str(),str.size());
    //接收
	socketSend->recvMsg();
    //接收
	socketSend->recvMsg();
}
//put
void FTP::commandPut(const string& commandStr)
{

    //提取文件路径
    char temp[1024] = {};
    sscanf(commandStr.c_str(),"put %s",temp);

    /*sprintf(buf,"TYPE A");
    printf("%s",buf);
    send(sockfd,buf,strlen(buf),0);
    bzero(buf,sizeof(buf));
    recv(sockfd,buf,sizeof(buf),0);
    printf("service:%s",buf);*/

    //SIZE命令
    socketSend->sendMsg("SIZE %s\n",temp);
    //接收
	socketSend->recvMsg();
    //获取新端口
    try{
        getNewPort();
    }catch(const char* ex){
        throw ex;
    }
	//读文件
    char file[4096] = {};
    int fd = open(temp,O_EXCL | O_RDWR,0744);
    if(0 > fd)
    {
        perror("open");
        return;
    }
    read(fd,file,sizeof(file));
    char time[255] = {};
    struct stat state = {};
    fstat(fd,&state);
    struct tm* stu = localtime(&(state.st_mtime));
    sprintf(time,"%d%02d%02d%02d%02d%2d",(stu->tm_year)+1900,(stu->tm_mon)+1,stu->tm_mday,stu->tm_hour,stu->tm_min,stu->tm_sec);
    //printf("%s\n",time);
    close(fd);

    //STOR命令
    socketSend->sendMsg("STOR %s\n",temp);
    //接收
	socketSend->recvMsg();
	//发送文件
	socketRecv->sendMsg(file);
    //
    delete socketRecv;
    socketRecv = NULL;
    qDebug("delete socketRecv");
    //接收
    //socketRecv->recvMsg();


    /*sprintf(buf,"PWD\n");
    send(sockfd,buf,strlen(buf),0);
    bzero(buf,sizeof(buf));
    recv(sockfd,buf,sizeof(buf),0);
    char path[4096] = {};
    sscanf(buf,"257 %s",path);
    printf("--%s\n",path);
    printf("--%s\n",time);
    printf("--%s\n",temp);*/
    //MDTM命令
    char buf[4096] = {};
    sprintf(buf,"MDTM %s ./%s\n",time,temp);
    socketSend->sendMsg(buf);
    //接收
	socketSend->recvMsg();

}
//put
void FTP::commandPut(const string& filePath,const string& fileName)
{
    //SIZE命令
    socketSend->sendMsg("SIZE %s\n",filePath.c_str());
    //接收
    socketSend->recvMsg();
    //获取新端口
    try{
        getNewPort();
    }catch(const char* ex){
        throw ex;
    }
    //读文件
    char file[4096] = {};
    int fd = open(filePath.c_str(),O_EXCL | O_RDWR,0744);
    if(0 > fd)
    {
        perror("open");
        return;
    }
    read(fd,file,sizeof(file));
    char time[255] = {};
    struct stat state = {};
    fstat(fd,&state);
    struct tm* stu = localtime(&(state.st_mtime));
    sprintf(time,"%d%02d%02d%02d%02d%2d",(stu->tm_year)+1900,(stu->tm_mon)+1,stu->tm_mday,stu->tm_hour,stu->tm_min,stu->tm_sec);
    //printf("%s\n",time);
    close(fd);
    //STOR命令
    socketSend->sendMsg("STOR %s\n",fileName.c_str());
    //接收
    socketSend->recvMsg();
    //发送文件
    socketRecv->sendMsg(string(file));
    delete socketRecv;
    socketRecv = NULL;
    //接收
    socketSend->recvMsg();
    //MDTM命令
    char buf[4096] = {};
    sprintf(buf,"MDTM %s ./%s\n",time,fileName.c_str());
    socketSend->sendMsg(buf);
    //接收
    socketSend->recvMsg();
}
//bye
void FTP::commandBye(void)
{
    //发送QUIT命令
	socketSend->sendMsg("QUIT\n");
    //接收
	socketSend->recvMsg();
}

 FTP::~FTP(void)
{
    commandBye();
    delete socketSend;
    delete socketRecv;
}

 FTP::FTP(int port,const char* ip_addr)
{
    //创建socket
    socketSend = new Socket(port,ip_addr);
    socketRecv = NULL;
    //接收
    socketSend->recvMsg();
    //连接服务器
    linkServer();
    //SYST命令
	socketSend->sendMsg("SYST\n");
    //接收
	socketSend->recvMsg();
	//FEAT命令
	socketSend->sendMsg("FEAT\n");
    //接收
    socketSend->recvMsg();
	//OPTS UTF8 ON命令
	socketSend->sendMsg("OPTS UTF8 ON\n");
    //接收
	socketSend->recvMsg();
    //PWD命令
	socketSend->sendMsg("PWD\n");
    //接收
	socketSend->recvMsg();
}

