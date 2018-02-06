#include "peoplemgr.h"
#include "ui_peoplemgr.h"
#include "SqlConn.h"
#include "mymessagebox.h"
#include "json.h"
#include <QSqlQuery>
#include <QDebug>
#include <QKeyEvent>

PeopleMgr::PeopleMgr(QWidget *control, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PeopleMgr)
{
    ui->setupUi(this);
    installEventFilter(control);
    page = 1;
    ui->pgup->setEnabled(false);
    isTail = false;
    isHead = true;
    isChg_row1 = false;
    isChg_row2 = false;
    isChg_row3 = false;
    isChg_row4 = false;
    connect(ui->check_11, SIGNAL(clicked()),SLOT(changeAuth1()));
    connect(ui->check_12, SIGNAL(clicked()),SLOT(changeAuth1()));
    connect(ui->check_13, SIGNAL(clicked()),SLOT(changeAuth1()));
    connect(ui->check_21, SIGNAL(clicked()),SLOT(changeAuth2()));
    connect(ui->check_22, SIGNAL(clicked()),SLOT(changeAuth2()));
    connect(ui->check_23, SIGNAL(clicked()),SLOT(changeAuth2()));
    connect(ui->check_31, SIGNAL(clicked()),SLOT(changeAuth3()));
    connect(ui->check_32, SIGNAL(clicked()),SLOT(changeAuth3()));
    connect(ui->check_33, SIGNAL(clicked()),SLOT(changeAuth3()));
    connect(ui->check_41, SIGNAL(clicked()),SLOT(changeAuth4()));
    connect(ui->check_42, SIGNAL(clicked()),SLOT(changeAuth4()));
    connect(ui->check_43, SIGNAL(clicked()),SLOT(changeAuth4()));
    QString qss = "QCheckBox::indicator{height:30px;width:30px;border-image:url(:/images/ept.png)} QCheckBox::indicator::checked{border-image:url(:/images/yes.png)}";
    setStyleSheet(qss);
    dataUpdate();
}

PeopleMgr::~PeopleMgr()
{
    delete ui;
}

void PeopleMgr::dataUpdate()
{
    QSqlQuery query(*Conn());
    QString sql = "SELECT name, permission FROM user LIMIT 5 OFFSET " + QString::number(page,10) + ";";
//    qDebug()<<sql;
    query.prepare(sql);
    if (!QueryRun(query, "取4条数据在第"+QString::number(page,10)+"页"))
        return;
    else
    {
        for (int i = 0; i < 4; i ++)
        {
            if (query.next())
            {
                changeMgr(i, query.value(0).toString(), query.value(1).toInt());
            }
            else
            {
                if (i == 0 && page >= 4)
                {
                    page -= 4;
                    dataUpdate();
                    return;
                }
                isTail = true;
                changeMgr(i, "", 0);
            }
        }
        if (!query.next())
            isTail = true;
    }
    ui->pgdn->setEnabled(!isTail);
    ui->pgdn->setHidden(isTail);
    ui->pgup->setEnabled(!isHead);
    ui->pgup->setHidden(isHead);
}

void PeopleMgr::changeMgr(int row, QString name, int auth)
{
    switch(row)
    {
    case 0:
        changeRow1(name, auth);
        break;
    case 1:
        changeRow2(name, auth);
        break;
    case 2:
        changeRow3(name, auth);
        break;
    case 3:
        changeRow4(name, auth);
        break;
    }
}

void PeopleMgr::changeRow1(QString name, int auth)
{
    if (name == "")
    {
        ui->user_1->hide();
        ui->check_11->hide();
        ui->check_12->hide();
        ui->check_13->hide();
        ui->del_1->hide();
        return;
    }
    else
    {
        ui->user_1->show();
        ui->check_11->show();
        ui->check_12->show();
        ui->check_13->show();
        ui->del_1->show();
    }
    ui->user_1->setText(name);
    auth & 4 ? ui->check_11->setChecked(true) : ui->check_11->setChecked(false);
    auth & 2 ? ui->check_12->setChecked(true) : ui->check_12->setChecked(false);
    auth & 1 ? ui->check_13->setChecked(true) : ui->check_13->setChecked(false);
}

void PeopleMgr::changeRow2(QString name, int auth)
{
    if (name == "")
    {
        ui->user_2->hide();
        ui->check_21->hide();
        ui->check_22->hide();
        ui->check_23->hide();
        ui->del_2->hide();
        return;
    }
    else
    {
        ui->user_2->show();
        ui->check_21->show();
        ui->check_22->show();
        ui->check_23->show();
        ui->del_2->show();
    }
    ui->user_2->setText(name);
    auth & 4 ? ui->check_21->setChecked(true) : ui->check_21->setChecked(false);
    auth & 2 ? ui->check_22->setChecked(true) : ui->check_22->setChecked(false);
    auth & 1 ? ui->check_23->setChecked(true) : ui->check_23->setChecked(false);
}

void PeopleMgr::changeRow3(QString name, int auth)
{
    if (name == "")
    {
        ui->user_3->hide();
        ui->check_31->hide();
        ui->check_32->hide();
        ui->check_33->hide();
        ui->del_3->hide();
        return;
    }
    else
    {
        ui->user_3->show();
        ui->check_31->show();
        ui->check_32->show();
        ui->check_33->show();
        ui->del_3->show();
    }
    ui->user_3->setText(name);
    auth & 4 ? ui->check_31->setChecked(true) : ui->check_31->setChecked(false);
    auth & 2 ? ui->check_32->setChecked(true) : ui->check_32->setChecked(false);
    auth & 1 ? ui->check_33->setChecked(true) : ui->check_33->setChecked(false);
}

void PeopleMgr::changeRow4(QString name, int auth)
{
    if (name == "")
    {
        ui->user_4->hide();
        ui->check_41->hide();
        ui->check_42->hide();
        ui->check_43->hide();
        ui->del_4->hide();
        return;
    }
    else
    {
        ui->user_4->show();
        ui->check_41->show();
        ui->check_42->show();
        ui->check_43->show();
        ui->del_4->show();
    }
    ui->user_4->setText(name);
    auth & 4 ? ui->check_41->setChecked(true) : ui->check_41->setChecked(false);
    auth & 2 ? ui->check_42->setChecked(true) : ui->check_42->setChecked(false);
    auth & 1 ? ui->check_43->setChecked(true) : ui->check_43->setChecked(false);
}

void PeopleMgr::on_pgup_clicked()
{
    if (isTail)
        isTail = false;
    page -= 4;
    if (page == 1)
        isHead = true;
    on_save_clicked();
    dataUpdate();
}

void PeopleMgr::on_pgdn_clicked()
{
    if (isHead)
        isHead = false;
    page += 4;
    on_save_clicked();
    dataUpdate();
}

void PeopleMgr::on_del_1_clicked()
{
    QSqlQuery query(*Conn());
    QString name = ui->user_1->text();
    QString sql = "DELETE FROM user WHERE name = '" + name + "';";
    query.prepare(sql);
    if (!QueryRun(query, "删除第一个用户"))
    {
        return;
    }
    else
    {
        dataUpdate();
    }
}

void PeopleMgr::on_del_2_clicked()
{
    QSqlQuery query(*Conn());
    QString name = ui->user_2->text();
    QString sql = "DELETE FROM user WHERE name = '" + name + "';";
    query.prepare(sql);
    if (!QueryRun(query, "删除第2个用户"))
    {
        return;
    }
    else
    {
        dataUpdate();
    }
}

void PeopleMgr::on_del_3_clicked()
{
    QSqlQuery query(*Conn());
    QString name = ui->user_3->text();
    QString sql = "DELETE FROM user WHERE name = '" + name + "';";
    query.prepare(sql);
    if (!QueryRun(query, "删除第3个用户"))
    {
        return;
    }
    else
    {
        dataUpdate();
    }
}

void PeopleMgr::on_del_4_clicked()
{
    QSqlQuery query(*Conn());
    QString name = ui->user_4->text();
    QString sql = "DELETE FROM user WHERE name = '" + name + "';";
    query.prepare(sql);
    if (!QueryRun(query, "删除第一个用户"))
    {
        return;
    }
    else
    {
        dataUpdate();
    }
}

void PeopleMgr::on_save_clicked()
{

        QVariantList names;
        QVariantList auths;
        int auth = 0;
        QString name = "";
        QSqlQuery query(*Conn());
        query.prepare("UPDATE user SET permission = ? WHERE name = ?");

        if (isChg_row1)
        {
            name = ui->user_1->text();


            ui->check_11->isChecked()? (auth |= 4) : (auth |= 0);
            ui->check_12->isChecked()? (auth |= 2) : (auth |= 0);
            ui->check_13->isChecked()? (auth |= 1) : (auth |= 0);
            names << name;
            auths << auth;
        }

        if (!ui->user_2->isHidden() && isChg_row2)
        {
            auth = 0;
            name = ui->user_2->text();
            ui->check_21->isChecked()? (auth |= 4) : (auth |= 0);
            ui->check_22->isChecked()? (auth |= 2) : (auth |= 0);
            ui->check_23->isChecked()? (auth |= 1) : (auth |= 0);
            names << name;
            auths << auth;
        }

        if (!ui->user_3->isHidden() && isChg_row3)
        {
            auth = 0;
            name = ui->user_3->text();
            ui->check_31->isChecked()? (auth |= 4) : (auth |= 0);
            ui->check_32->isChecked()? (auth |= 2) : (auth |= 0);
            ui->check_33->isChecked()? (auth |= 1) : (auth |= 0);
            names << name;
            auths << auth;
        }

        if (!ui->user_4->isHidden() && isChg_row4)
        {
            auth = 0;
            name = ui->user_4->text();

            ui->check_41->isChecked()? (auth |= 4) : (auth |= 0);
            ui->check_42->isChecked()? (auth |= 2) : (auth |= 0);
            ui->check_43->isChecked()? (auth |= 1) : (auth |= 0);
            names << name;
            auths << auth;
        }
//        qDebug()<<auths;
//        qDebug()<<names;
        query.addBindValue(auths);
        query.addBindValue(names);
        if (isChg_row1 || isChg_row2 || isChg_row3 || isChg_row4)
        {
            if (!QueryRun(query, "更新权限", "batch"))
            {
                return;
            }
            else
            {
                isChg_row1 = false;
                isChg_row2 = false;
                isChg_row3 = false;
                isChg_row4 = false;
            }
        }
        dataUpdate();
}

void PeopleMgr::recvMsg(char *msg)
{
    Q_UNUSED(msg)
//    cJSON* root = cJSON_Parse(msg);
//    cJSON* type = cJSON_GetObjectItem(root, "type");
//    cJSON*
}

void PeopleMgr::changeAuth1()
{
    isChg_row1 = true;
}

void PeopleMgr::changeAuth2()
{
    isChg_row2 = true;
}

void PeopleMgr::changeAuth3()
{
    isChg_row3 = true;
}

void PeopleMgr::changeAuth4()
{
    isChg_row4 = true;
}

void PeopleMgr::on_exit_clicked()
{
    emit display(0);
    on_save_clicked();
    page = 1;
}

void PeopleMgr::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
    {
        on_exit_clicked();
    }
}
