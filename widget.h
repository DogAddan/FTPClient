#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QIcon>
#include "FTP.h"
#include <QDir>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void on_editclientDir_editingFinished();

    void on_listClientDir_doubleClicked(const QModelIndex &index);

    void on_btnCommect_clicked();

    void on_eidtServerDir_editingFinished();

    void on_listServerDir_doubleClicked(const QModelIndex &index);

    void on_btnDownLoad_clicked();

    void on_btnUpLoad_clicked();

private:
    Ui::Widget *ui;
    //
    QDir* dir;
    //
    FTP* ftp;
    //更新ListWidget
    void updateListWidget(QListWidget*,const QStringList&);
    //获取服务器文件列表
    void getServerDirList(QStringList&);
};

#endif // WIDGET_H
