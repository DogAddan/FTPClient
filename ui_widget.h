/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue Mar 26 09:37:15 2019
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label1;
    QLineEdit *editIp;
    QLineEdit *editUserName;
    QLabel *label2;
    QLineEdit *editPassword;
    QLabel *label3;
    QLineEdit *editPort;
    QLabel *label4;
    QPushButton *btnCommect;
    QLabel *label5;
    QLineEdit *editclientDir;
    QLineEdit *eidtServerDir;
    QLabel *label6;
    QListWidget *listClientDir;
    QListWidget *listServerDir;
    QPushButton *btnUpLoad;
    QPushButton *btnDownLoad;
    QLabel *labelClientDirTip;
    QLabel *labelServerDirTip;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        label1 = new QLabel(Widget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(40, 40, 60, 30));
        editIp = new QLineEdit(Widget);
        editIp->setObjectName(QString::fromUtf8("editIp"));
        editIp->setGeometry(QRect(110, 40, 90, 30));
        editUserName = new QLineEdit(Widget);
        editUserName->setObjectName(QString::fromUtf8("editUserName"));
        editUserName->setGeometry(QRect(300, 40, 90, 30));
        label2 = new QLabel(Widget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(219, 40, 71, 30));
        editPassword = new QLineEdit(Widget);
        editPassword->setObjectName(QString::fromUtf8("editPassword"));
        editPassword->setGeometry(QRect(491, 40, 90, 30));
        editPassword->setEchoMode(QLineEdit::Password);
        label3 = new QLabel(Widget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(410, 40, 71, 30));
        editPort = new QLineEdit(Widget);
        editPort->setObjectName(QString::fromUtf8("editPort"));
        editPort->setGeometry(QRect(630, 40, 30, 30));
        label4 = new QLabel(Widget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(590, 40, 40, 30));
        btnCommect = new QPushButton(Widget);
        btnCommect->setObjectName(QString::fromUtf8("btnCommect"));
        btnCommect->setGeometry(QRect(680, 39, 100, 30));
        label5 = new QLabel(Widget);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(30, 110, 66, 30));
        editclientDir = new QLineEdit(Widget);
        editclientDir->setObjectName(QString::fromUtf8("editclientDir"));
        editclientDir->setGeometry(QRect(110, 110, 200, 30));
        eidtServerDir = new QLineEdit(Widget);
        eidtServerDir->setObjectName(QString::fromUtf8("eidtServerDir"));
        eidtServerDir->setGeometry(QRect(510, 110, 200, 30));
        label6 = new QLabel(Widget);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(430, 110, 66, 30));
        listClientDir = new QListWidget(Widget);
        listClientDir->setObjectName(QString::fromUtf8("listClientDir"));
        listClientDir->setGeometry(QRect(30, 200, 301, 351));
        listServerDir = new QListWidget(Widget);
        listServerDir->setObjectName(QString::fromUtf8("listServerDir"));
        listServerDir->setGeometry(QRect(430, 200, 301, 351));
        btnUpLoad = new QPushButton(Widget);
        btnUpLoad->setObjectName(QString::fromUtf8("btnUpLoad"));
        btnUpLoad->setGeometry(QRect(340, 290, 71, 27));
        btnDownLoad = new QPushButton(Widget);
        btnDownLoad->setObjectName(QString::fromUtf8("btnDownLoad"));
        btnDownLoad->setGeometry(QRect(340, 420, 71, 27));
        labelClientDirTip = new QLabel(Widget);
        labelClientDirTip->setObjectName(QString::fromUtf8("labelClientDirTip"));
        labelClientDirTip->setGeometry(QRect(110, 150, 201, 30));
        labelClientDirTip->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 4);"));
        labelServerDirTip = new QLabel(Widget);
        labelServerDirTip->setObjectName(QString::fromUtf8("labelServerDirTip"));
        labelServerDirTip->setGeometry(QRect(510, 150, 201, 30));
        labelServerDirTip->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 4);"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("Widget", "serverip", 0, QApplication::UnicodeUTF8));
        editIp->setText(QApplication::translate("Widget", "192.168.6.66", 0, QApplication::UnicodeUTF8));
        editUserName->setText(QApplication::translate("Widget", "EOS1811", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("Widget", "username", 0, QApplication::UnicodeUTF8));
        editPassword->setText(QApplication::translate("Widget", "ooss1811", 0, QApplication::UnicodeUTF8));
        label3->setText(QApplication::translate("Widget", "password", 0, QApplication::UnicodeUTF8));
        editPort->setText(QApplication::translate("Widget", "21", 0, QApplication::UnicodeUTF8));
        label4->setText(QApplication::translate("Widget", "port", 0, QApplication::UnicodeUTF8));
        btnCommect->setText(QApplication::translate("Widget", "connect", 0, QApplication::UnicodeUTF8));
        label5->setText(QApplication::translate("Widget", "clientdir", 0, QApplication::UnicodeUTF8));
        editclientDir->setText(QApplication::translate("Widget", "/", 0, QApplication::UnicodeUTF8));
        eidtServerDir->setText(QApplication::translate("Widget", "/", 0, QApplication::UnicodeUTF8));
        label6->setText(QApplication::translate("Widget", "serverdir", 0, QApplication::UnicodeUTF8));
        btnUpLoad->setText(QApplication::translate("Widget", ">>", 0, QApplication::UnicodeUTF8));
        btnDownLoad->setText(QApplication::translate("Widget", "<<", 0, QApplication::UnicodeUTF8));
        labelClientDirTip->setText(QString());
        labelServerDirTip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
