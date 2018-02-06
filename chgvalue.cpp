#include "chgvalue.h"
#include "ui_chgvalue.h"
#include "SqlConn.h"
#include "QDateTime"

ChgValue::ChgValue(QString city, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChgValue)
{
    ui->setupUi(this);
    this->city = city;
//    setStyleSheet("QLineEdit{border-color: red;}");
    QString sql = "SELECT temp, pm10, pm25, so2, quality, time FROM city WHERE name = '%1'";
    QSqlQuery query(*Conn());
    query.prepare(sql.arg(city));
    if (!QueryRun(query, tr("查询%1数据").arg(city)))
    {
        return;
    }
    if (query.next())
    {
        ui->city->setText(city);
        ui->temp->setText(query.value(0).toString());
        ui->pm10->setText(query.value(1).toString());
        ui->pm25->setText(query.value(2).toString());
        ui->so2->setText(query.value(3).toString());
        ui->quality->setText(query.value(4).toString());
        ui->time->setText(query.value(5).toString());
    }
    else
    {
        return;
    }

}

ChgValue::~ChgValue()
{
    delete ui;
}

void ChgValue::on_pushButton_clicked()
{
    bool ok;
    bool isChg = false;
    QString qss_t = "#%1{border-color:red;border-width: 2px;border-style: solid}";
    QString qss;
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
        QSqlQuery query(*Conn());
        QString sql = "UPDATE city SET temp=?, pm10=?, pm25=?, so2=?, quality=?, time=? WHERE name=?";
        query.prepare(sql);
        query.addBindValue(temp);
        query.addBindValue(pm10);
        query.addBindValue(pm25);
        query.addBindValue(so2);
        query.addBindValue(quality);
        query.addBindValue(time);
        query.addBindValue(this->city);
        if (!QueryRun(query, tr("更新%1的数据").arg(this->city)))
        {
            qDebug()<<"Error!";
            return;
        }
        ui->time->setText(time);
        setStyleSheet("QLineEdit{border-color:black;}");
    }
}

void ChgValue::on_pushButton_2_clicked()
{
    emit doChg();
    this->close();
    delete this;
}
