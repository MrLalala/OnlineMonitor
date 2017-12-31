#include "mymessagebox.h"
#include "ui_mymessagebox.h"
#include "QDebug"

MyMessageBox::MyMessageBox(QString title, QString msg, QString type, QString flag, QString yes, QString no, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    ui->yes->setText(yes);
    if (no == "")
    {
        ui->no->hide();
        ui->yes->move(115,140);
    }
    else
    {
        ui->no->setText(no);
    }
    setWindowTitle(title);
    ui->msg->setText(msg);
    QString qss = "MyMessageBox{border-image: url(:/images/main2.jpg);} #type{border-image:url(:/images/%1.png);}#msg,QPushButton{font-family: Microsoft YaHei UI; font-size: 18px;color: white;background-color: rgba(0,0,0,0);}";
    setStyleSheet(qss.arg(type));
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "flag", flag.toStdString().c_str());
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}


void MyMessageBox::on_yes_clicked()
{
    cJSON_AddStringToObject(root, "type", "yes");
    emit sendMsg(cJSON_Print(root));
}

void MyMessageBox::on_no_clicked()
{
    cJSON_AddStringToObject(root, "type", "no");
    emit sendMsg(cJSON_Print(root));
}
