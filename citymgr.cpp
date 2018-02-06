#include "citymgr.h"
#include "ui_citymgr.h"
#include "SqlConn.h"
#include "QDateTime"
#include "chgvalue.h"
#include "addcity.h"

CityMgr::CityMgr(QWidget* mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CityMgr)
{
    ui->setupUi(this);
    isHead = true;
    isTail = false;
    page = 0;
    installEventFilter(mainW);
//    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    dataUpdate();
}

CityMgr::~CityMgr()
{
    delete ui;
}

void CityMgr::dataUpdate()
{
    QSqlQuery query(*Conn());
    QString sql = "SELECT name, time FROM city LIMIT 5 OFFSET " + QString::number(page,10) + ";";
    query.prepare(sql);
    if (!QueryRun(query, "取4条数据在第"+QString::number(page,10)+"页"))
        return;
    else
    {
        for (int i = 0; i < 4; i ++)
        {
            if (query.next())
            {
//                qDebug()<<query.value(1);
                changeMgr(i, query.value(0).toString(), query.value(1).toString());
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
                changeMgr(i, "", "");
            }
        }
        if (!query.next())
            isTail = true;
        else
            isTail = false;
    }
//    qDebug()<<isTail<<isHead;
    ui->pgdn->setEnabled(!isTail);
    ui->pgdn->setHidden(isTail);
    ui->pgup->setEnabled(!isHead);
    ui->pgup->setHidden(isHead);
}

void CityMgr::changeRow1(QString name, QDateTime time)
{
    if (name == "")
    {
        ui->city_1->hide();
        ui->del_1->hide();
        ui->update_1->hide();
        ui->show_1->hide();
        ui->time_1->hide();
    }
    else
    {
        ui->city_1->show();
        ui->del_1->show();
        ui->update_1->show();
        ui->show_1->show();
        ui->time_1->show();
        ui->city_1->setText(name);
        ui->time_1->setText(getTime(time));
    }
}

void CityMgr::changeRow2(QString name, QDateTime time)
{
    if (name == "")
    {
        ui->city_2->hide();
        ui->del_2->hide();
        ui->update_2->hide();
        ui->show_2->hide();
        ui->time_2->hide();
    }
    else
    {
        ui->city_2->show();
        ui->del_2->show();
        ui->update_2->show();
        ui->show_2->show();
        ui->time_2->show();
        ui->city_2->setText(name);
        ui->time_2->setText(getTime(time));
    }
}

void CityMgr::changeRow3(QString name, QDateTime time)
{
    if (name == "")
    {
        ui->city_3->hide();
        ui->del_3->hide();
        ui->update_3->hide();
        ui->show_3->hide();
        ui->time_3->hide();
    }
    else
    {
        ui->city_3->show();
        ui->del_3->show();
        ui->update_3->show();
        ui->show_3->show();
        ui->time_3->show();
        ui->city_3->setText(name);
        ui->time_3->setText(getTime(time));
    }
}

void CityMgr::changeRow4(QString name, QDateTime time)
{
    if (name == "")
    {
        ui->city_4->hide();
        ui->del_4->hide();
        ui->update_4->hide();
        ui->show_4->hide();
        ui->time_4->hide();
    }
    else
    {
        ui->city_4->show();
        ui->del_4->show();
        ui->update_4->show();
        ui->show_4->show();
        ui->time_4->show();
        ui->city_4->setText(name);
//        qDebug()<<getTime(time);
        ui->time_4->setText(getTime(time));
    }
}

void CityMgr::changeMgr(int row, QString name, QString time)
{
    QDateTime dtime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    switch (row) {
    case 0:
        changeRow1(name, dtime);
        break;
    case 1:
        changeRow2(name, dtime);
        break;
    case 2:
        changeRow3(name, dtime);
        break;
    case 3:
        changeRow4(name, dtime);
        break;
    }
}

void CityMgr::on_pgdn_clicked()
{
    if (isHead)
        isHead = false;
    page += 4;
//    on_save_clicked();
    dataUpdate();
}

void CityMgr::on_pgup_clicked()
{
    if (isTail)
        isTail = false;
    page -= 4;
    if (page == 0)
        isHead = true;
//    on_save_clicked();
    dataUpdate();
}

QString CityMgr::getTime(QDateTime dtime)
{
    qint64 time = dtime.msecsTo(QDateTime::currentDateTime());
    if (time < 3600000)
        return "1小时内";
    else if (time <  86400000)
        return tr("%1小时前").arg(time/3600000);
    else
        return tr("%1天前").arg(time/86400000);
}

void CityMgr::on_update_1_clicked()
{
    showChg(1);
}

void CityMgr::on_update_2_clicked()
{
    showChg(2);
}

void CityMgr::on_update_3_clicked()
{
    showChg(3);
}

void CityMgr::on_update_4_clicked()
{
    showChg(4);
}

void CityMgr::showChg(int layer)
{
    switch (layer)
    {
    case 1:
        temp = new ChgValue(ui->city_1->text());
        break;
    case 2:
        temp = new ChgValue(ui->city_2->text());
        break;
    case 3:
        temp = new ChgValue(ui->city_3->text());
        break;
    case 4:
        temp = new ChgValue(ui->city_4->text());
        break;
    }
    connect(temp, SIGNAL(doChg()),SLOT(dataUpdate()));
    temp->setModal(true);
    temp->show();
}

void CityMgr::on_newC_clicked()
{
    AddCity* city = new AddCity;
    city->setModal(true);
    connect(city, SIGNAL(onCrt()), SLOT(dataUpdate()));
    city->show();
}

void CityMgr::on_del_1_clicked()
{
    delCity(1);
}


void CityMgr::on_del_2_clicked()
{
    delCity(2);
}

void CityMgr::on_del_3_clicked()
{
    delCity(3);
}

void CityMgr::on_del_4_clicked()
{
    delCity(4);
}

void CityMgr::delCity(int num)
{
    QString city = "";
    switch(num)
    {
    case 1:
        city = ui->city_1->text();
        break;
    case 2:
        city = ui->city_2->text();
        break;
    case 3:
        city = ui->city_3->text();
    case 4:
        city = ui->city_4->text();
        break;
    }
    QString sql = "DELETE FROM city WHERE name = ?";
    QSqlQuery query(*Conn());
    query.prepare(sql);
    query.addBindValue(city);
    if (!QueryRun(query, tr("删除第%1个城市：%2").arg(QString::number(num), city)))
    {
        return;
    }
    dataUpdate();
}

void CityMgr::showCity(int num)
{
    switch(num)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
}

void CityMgr::on_exit_clicked()
{
    emit display(0);
    this->page = 0;
    dataUpdate();
}

void CityMgr::on_show_1_clicked()
{
    emit send_back(2);
    emit display(3);
    emit select_city(ui->city_1->text());
}

void CityMgr::on_show_2_clicked()
{
    emit send_back(2);
    emit display(3);
    emit select_city(ui->city_2->text());
}

void CityMgr::on_show_3_clicked()
{
    emit send_back(2);
    emit display(3);
    emit select_city(ui->city_3->text());
}

void CityMgr::on_show_4_clicked()
{
    emit send_back(2);
    emit display(3);
    emit select_city(ui->city_4->text());
}
