#include "chgpsd.h"
#include "ui_chgpsd.h"
#include "SqlConn.h"
#include <QSqlQuery>
#include "mymessagebox.h"
#include <QDebug>


ChgPsd::ChgPsd(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChgPsd)
{
    ui->setupUi(this);
    this->name = name;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    QString qss = "#ChgPsd{border-image: url(:/images/main2.jpg);}";
    qss += "QPushButton,QLabel,QLineEdit{font-family: Microsoft YaHei UI; font-size: 15px;color: white;background-color: rgba(0,0,0,0);}";
    setStyleSheet(qss);
}

ChgPsd::~ChgPsd()
{
    delete ui;
}

void ChgPsd::on_submit_clicked()
{
    ui->newerr->clear();
    ui->nowerr->clear();
    QString nowPsd = ui->nowpsd->text();
    QSqlQuery query(*Conn());
    QString sql = "SELECT * FROM user WHERE name = '" + name + "' and password = '" + nowPsd +"';";
//    qDebug()<<sql;
    query.prepare(sql);
    if (!QueryRun(query, "判断密码是否正确"))
    {
        return;
    }
    if (!query.next())
    {
        ui->nowerr->setText("当前密码不正确");
        ui->nowpsd->setFocus();
        return;
    }
    else
    {
        if (ui->psd->text() != ui->repsd->text())
        {
            ui->newerr->setText("两次密码不相同！");
            return;
        }
        else
        {
            sql = "UPDATE user SET password = '" + ui->psd->text() + "' WHERE name = '"+name+"';";
//            qDebug()<<sql;
            query.prepare(sql);
            if (!QueryRun(query, "更新密码"))
            {
                return;
            }
            else
            {
                MyMessageBox* temp = new MyMessageBox("成功","修改成功！","ok","","确定","");
                connect(temp, SIGNAL(sendMsg(char*)),SLOT(close()));
                connect(temp, SIGNAL(sendMsg(char*)), temp, SLOT(close()));
                temp->setModal(true);
                temp->show();
            }
        }
    }
}
