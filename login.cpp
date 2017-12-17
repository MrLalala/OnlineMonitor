#include "ui_login.h"
#include "login.h"

Login::Login(QWidget *mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    installEventFilter(mainW);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{

}

void Login::on_signin_clicked()
{
    ui->name->clear();
    ui->name_error->clear();
    ui->password->clear();
    ui->psd_error->clear();
    emit display(1);
}


void Login::on_about_clicked()
{
    emit display(2);
}

void Login::on_exit_clicked()
{
    this->close();
    emit closeW();
}
