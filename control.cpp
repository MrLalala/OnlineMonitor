#include "control.h"
#include "ui_control.h"
#include "mymessagebox.h"
#include "mainwidget.h"
#include "json.h"
#include <QStackedLayout>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QKeyEvent>
#include "chgpsd.h"

Control::Control(QWidget* mainW, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Control)
{
    ui->setupUi(this);
    installEventFilter(mainW);
    QTimer* time = new QTimer(this);
    connect(time, SIGNAL(timeout()), SLOT(timeUpdate()));
    time->start(1000);
}

Control::~Control()
{
    delete ui;
}

void Control::showUser(QString name)
{
    this->name = name;
    ui->user->setText("欢迎！"+name);
}

void Control::on_user_clicked()
{
    message = new MyMessageBox("提示","是否注销？","query","注销");
    message->setModal(true);
    connect(message,SIGNAL(sendMsg(char*)),SLOT(recvMsg(char*)));
    message->show();
}

void Control::recvMsg(char *msg)
{
    cJSON* root = cJSON_Parse(msg);
    cJSON* flag = cJSON_GetObjectItem(root, "flag");
    cJSON* type = cJSON_GetObjectItem(root, "type");

    if (QString(flag->valuestring) == "注销")
    {
        if (QString(type->valuestring) == "yes")
        {
            MainWidget* temp = new MainWidget;
            temp->show();
            message->close();
            emit closeW();
            this->close();
//            qDebug()<<"注销";
            return;
        }
        else
        {
            message->close();
        }
    }
    if (QString(flag->valuestring) == "退出")
    {
        if (QString(type->valuestring) == "yes")
        {
            emit closeW();
            message->close();
            this->close();
            return;
        }
        else
        {
            message->close();
        }
    }
    delete message;
}

void Control::timeUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->time->setText(str);
}

void Control::on_exit_clicked()
{
    message = new MyMessageBox("退出","是否退出？","query","退出");
    message->setModal(true);
    connect(message,SIGNAL(sendMsg(char*)),SLOT(recvMsg(char*)));
    message->show();
}

void Control::on_psdChg_clicked()
{
    ChgPsd* chg = new ChgPsd(this->name);
    chg->setModal(true);
    chg->show();
}

void Control::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
    {
        on_exit_clicked();
    }
}

void Control::on_userMgr_clicked()
{
    emit display(1);
}

void Control::on_cityMgr_clicked()
{
    emit display(2);
}

void Control::on_showData_clicked()
{
    emit display(3);
    emit send_back(0);
}
