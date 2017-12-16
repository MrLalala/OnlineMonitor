#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
//    去除窗体边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
//    设置自动填充的背景
    QString qss = "Login{border-image: url(:/images/main2.jpg);}";
//    设着按钮透明无边框
    qss += "QToolButton{color:white;background-color:rgba(0,0,0,0);border-style:none;}";
//    设置输入框透明
    qss += "QLineEdit{color: white;background-color: rgba(0,0,0,0);}";
//    设置QLabel字体颜色为白色
    qss += "QLabel{color:white;}";
    setStyleSheet(qss);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{

}
