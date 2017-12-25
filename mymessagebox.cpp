#include "mymessagebox.h"
#include "ui_mymessagebox.h"
#include "json.h"
#include "QDebug"

MyMessageBox::MyMessageBox(QString title, QString msg, QString type, QString yes, QString no, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    ui->yes->setText(yes);
    ui->no->setText(no);
    setWindowTitle(title);
    ui->msg->setText(msg);
    QString qss = "MyMessageBox{border-image: url(:/images/main2.jpg);} #type{border-image:url(:/images/%1.png);}#msg,QPushButton{font-family: Microsoft YaHei UI; font-size: 18px;color: white;background-color: rgba(0,0,0,0);}";
    setStyleSheet(qss.arg(type));
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}


void MyMessageBox::on_yes_clicked()
{
    cJSON* root;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "yes");
    emit sendMsg(cJSON_Print(root));
}

void MyMessageBox::on_no_clicked()
{
    cJSON* root;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "no");
    emit sendMsg(cJSON_Print(root));
}
