#include "ui_login.h"
#include "login.h"
#include "SqlConn.h"
#include "maincontrol.h"
#include <QKeyEvent>

Login::Login(QWidget *mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    installEventFilter(mainW);
    ui->name->setFocus();
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    ui->name_error->clear();
    ui->psd_error->clear();
    bool flag = true;
    QString name = ui->name->text();
    QString psd = ui->password->text();
    if (name == NULL)
    {
        ui->name_error->setText("请输入用户名！");
        flag = false;
    }
    if (psd == NULL)
    {
        ui->psd_error->setText("请输入密码！");
        flag = false;
    }
    if (flag)
    {
        QSqlDatabase* now = Conn();
        QSqlQuery query(*now);
        QString sql = "SELECT * FROM user WHERE name = '" + name + "'";
        query.prepare(sql);
        if (!QueryRun(query, "查找用户"))
        {
            return;
        }
        if (!query.next())
        {
            ui->name_error->setText("请输入正确的用户名！");
        }
        else {
            sql += " AND password = '" + psd + "'";
            query.prepare(sql);
            if (!QueryRun(query, "验证用户"))
            {
                return;
            }
            if (!query.next())
            {
                ui->psd_error->setText("请输入正确的密码！");
            }
            else
            {
                MainControl* c = new MainControl();
                connect(this,SIGNAL(userLogin(QString)),c,SLOT(getName(QString)));
                c->show();
                emit userLogin(ui->name->text());
                emit(closeW());
                this->close();
            }
        }
    }

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

void Login::onEnter()
{
    on_login_clicked();
}
