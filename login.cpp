#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setStyleSheet("Login{border-image: url(:/images/main2.jpg);}");
}

Login::~Login()
{
    delete ui;
}
