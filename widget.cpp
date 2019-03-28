#include "widget.h"
#include "ui_widget.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化FTP
    ftp = NULL;
    //初始化文件夹对象
    dir = new QDir("/home/zhizhen");
    //更新ClientListWidget
    updateListWidget(ui->listClientDir,dir->entryList());
}

Widget::~Widget()
{
    delete dir;
    delete ftp;
    delete ui;
}
//更新ListWidget
void Widget::updateListWidget(QListWidget* listWiget,const QStringList& strList)
{
    //清空listWidget
    listWiget->clear();
    //添加item
    listWiget->addItems(strList);
    //排序item
    listWiget->sortItems();
}
//获取服务器文件列表
void Widget::getServerDirList(QStringList& fileList)
{
    //
    string str;
    try{
        ftp->commandLs(str);
    }catch(const char* ex){
        qDebug() << ex;
        ui->labelServerDirTip->setText("服务器连接失败!");
        return;
    }
    //cout << str << endl;
    //
    QStringList list = QString(str.c_str()).split("\n",QString::SkipEmptyParts);
    //
    QList<QString>::iterator it = list.begin();
    while(list.end()!=it)
    {
        QStringList oneFileList = it->split(" ",QString::SkipEmptyParts);
        oneFileList[8].resize(oneFileList[8].size()-1);
        fileList.push_back(oneFileList[8]);
        it++;
    }
}
//
void Widget::on_editclientDir_editingFinished()
{
    ui->labelClientDirTip->setText("");
    //获取路径
    QString path = ui->editclientDir->text();
    path = "/home/zhizhen" + path;
    //更新文件夹路径
    dir->setPath(path);
    //更新ClientListWidget
    updateListWidget(ui->listClientDir,dir->entryList());
}

void Widget::on_listClientDir_doubleClicked(const QModelIndex &)
{
    //移动到指定目录
    dir->cd(ui->listClientDir->currentItem()->text());
    //更新本地路径输入框
    ui->editclientDir->setText(dir->canonicalPath().remove("/home/zhizhen")+"/");
    //更新ClientListWidget
    updateListWidget(ui->listClientDir,dir->entryList());
}

void Widget::on_btnCommect_clicked()
{
    //创建FTP
    ftp = new FTP(ui->editPort->text().toInt(),ui->editIp->text().toStdString().c_str());
    //获取服务器当前路径的文件名链表
    QStringList fileList;
    getServerDirList(fileList);
    //更新ClientListWidget
    updateListWidget(ui->listServerDir,fileList);
    //
    ui->labelServerDirTip->setText("");
}

void Widget::on_eidtServerDir_editingFinished()
{
    //
    if(NULL == ftp)
    {
        ui->labelServerDirTip->setText("服务器未连接!");
        return;
    }
    //
    ui->labelServerDirTip->setText("");
    //移动路径
    QString commandCd = "cd " + ui->eidtServerDir->text();
    ftp->commandCd(commandCd.toStdString());
    //获取服务器当前路径的文件名链表
    QStringList fileList;
    getServerDirList(fileList);
    //更新ClientListWidget
    updateListWidget(ui->listServerDir,fileList);
}

void Widget::on_listServerDir_doubleClicked(const QModelIndex &)
{
    //移动到指定目录
    string path;
    QString cd = "cd " + ui->listServerDir->currentItem()->text();
    ftp->commandCd(cd.toStdString(),path);
    //更新本地路径输入框
    ui->eidtServerDir->setText(QString(path.c_str()));
    //获取服务器当前路径的文件名链表
    QStringList fileList;
    getServerDirList(fileList);
    //更新ServerListWidget
    updateListWidget(ui->listServerDir,fileList);
}

void Widget::on_btnDownLoad_clicked()
{
    QString get = "get " + ui->listServerDir->currentItem()->text();
    ftp->commandGet(get.toStdString());
    //更新ClientListWidget
    updateListWidget(ui->listClientDir,dir->entryList());
}

void Widget::on_btnUpLoad_clicked()
{
    QString put = "/home/zhizhen" + ui->editclientDir->text()+ui->listClientDir->currentItem()->text();
    qDebug() << put.toStdString().c_str();
    QStringList fileList;
    try{
        //上传文件
        ftp->commandPut(put.toStdString(),ui->listClientDir->currentItem()->text().toStdString());
        //获取服务器当前路径的文件名链表

        getServerDirList(fileList);
    }catch(const char* ex){
        qDebug() << ex;
        return;
    }

    //更新ServerListWidget
    updateListWidget(ui->listServerDir,fileList);
}
