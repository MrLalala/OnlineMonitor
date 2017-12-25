#include "control.h"
#include "ui_control.h"
#include "mymessagebox.h"
#include "mainwidget.h"
#include "json.h"
#include <QStackedLayout>
#include <QTimer>
#include <QDateTime>

Control::Control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control)
{
    ui->setupUi(this);
    this->InitWindow();
    QTimer* time = new QTimer(this);
    connect(time, SIGNAL(timeout()), SLOT(timeUpdate()));
    time->start(1000);
}

Control::~Control()
{
    delete ui;
}

void Control::InitWindow()
{
    QString qss = QString("QWidget#Control{border-image: url(:/images/main2.jpg);}");
    qss += "QToolButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;}";
    qss += "MyButton{color:black;font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "#time{color:white;font-family: Microsoft YaHei UI; font-size: 15px;}";
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setStyleSheet(qss);
}

void Control::showUser(QString name)
{
    ui->user->setText("欢迎！"+name);
}

void Control::on_user_clicked()
{
    message = new MyMessageBox("提示","是否注销？","query","是","否");
    message->setModal(true);
    connect(message,SIGNAL(sendMsg(char*)),SLOT(recvMsg(char*)));
    message->show();
}

void Control::recvMsg(char *msg)
{
    cJSON* root = cJSON_Parse(msg);
    cJSON* type = cJSON_GetObjectItem(root, "type");
    if (QString(type->valuestring) == "yes")
    {
        MainWidget* temp = new MainWidget;
        temp->show();
        message->close();
        this->close();
    }
    else
    {
        message->close();
    }
}

void Control::timeUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->time->setText(str);
}
