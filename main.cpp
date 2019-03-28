#include <QtGui/QApplication>
#include <QTextCodec>
#include "widget.h"

int main(int argc, char *argv[])
{
    //设置内部字符编码
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    
    return a.exec();
}
