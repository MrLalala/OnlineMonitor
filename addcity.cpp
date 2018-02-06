#include "addcity.h"
#include "ui_addcity.h"
#include "SqlConn.h"
#include <QDateTime>

AddCity::AddCity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCity)
{
    ui->setupUi(this);
}

AddCity::~AddCity()
{
    delete ui;
}

void AddCity::on_pushButton_clicked()
{
    QString sql;
    QSqlQuery query(*Conn());

    bool ok;
    bool isChg = false;
    QString qss_t = "#%1{border-color:red;border-width: 2px;border-style: solid}";
    QString qss;
    QString city = ui->city->text();
    if (city == NULL)
    {
        qss += qss_t.arg("city");
        isChg = true;
    }
    else
    {
      sql  = "SELECT time FROM city WHERE name = ?";
      query.prepare(sql);
      query.addBindValue(city);
      if (!QueryRun(query, tr("查找%1城市是否存在").arg(city)))
      {
          return;
      }
      if (query.next())
      {
          ui->name_error->setText("该城市已存在!");
          isChg = true;
      }
      else
          ui->name_error->setText("");
    }
    int temp = ui->temp->text().toInt(&ok);
    if (!ok || temp < 0)
    {
        qss += qss_t.arg("temp");
        isChg = true;
    }
    int pm10 = ui->pm10->text().toInt(&ok);
    if (!ok || pm10 < 0)
    {
        qss += qss_t.arg("pm10");
        isChg = true;
    }
    int pm25 = ui->pm25->text().toInt(&ok);
    if (!ok || pm25 < 0)
    {
        qss += qss_t.arg("pm25");
        isChg = true;
    }
    int so2 = ui->so2->text().toInt(&ok);
    if (!ok || so2 < 0)
    {
        qss += qss_t.arg("so2");
        isChg = true;
    }
    int quality = ui->quality->text().toInt(&ok);
    if (!ok || quality < 0)
    {
        qss += qss_t.arg("quality");
        isChg = true;
    }
    if (isChg)
    {
        setStyleSheet(qss);
        return;
    }
    else
    {
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        sql = "INSERT INTO city (name, temp, pm10, pm25, so2, quality, time) VALUES(?,?,?,?,?,?,?)";

        query.prepare(sql);
        query.addBindValue(city);
        query.addBindValue(temp);
        query.addBindValue(pm10);
        query.addBindValue(pm25);
        query.addBindValue(so2);
        query.addBindValue(quality);
        query.addBindValue(time);
        if (!QueryRun(query, tr("添加%1城市").arg(city)))
        {
            return;
        }
        emit onCrt();
        this->close();
    }


}

void AddCity::on_pushButton_2_clicked()
{
    this->close();
}
