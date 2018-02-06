#include "detail.h"
#include "ui_detail.h"
#include "SqlConn.h"
#include <QDateTime>
#include <QPropertyAnimation>

Detail::Detail(QWidget* mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Detail)
{
    ui->setupUi(this);

    isHead = true;
    isTail = false;
    page = 0;

    ui->temp->setTextVisible(false);
    ui->pm10->setTextVisible(false);
    ui->pm25->setTextVisible(false);
    ui->so2->setTextVisible(false);
    ui->quality->setTextVisible(false);
    ui->temp->setRange(-20, 50);
    ui->pm10->setRange(0, 100);
    ui->pm25->setRange(0, 100);
    ui->so2->setRange(0, 100);
    ui->quality->setRange(0, 300);
    qss = "QProgressBar{border:1px;background-color:transparent;}";
    setStyleSheet(qss);
    installEventFilter(mainW);
    _InitMap();
    dataUpdate();
    _Chg_Value("南京");
}

Detail::~Detail()
{
    delete ui;
}

void Detail::_InitMap()
{
    QSqlQuery query(*Conn());
    QString sql = "SELECT * FROM info";
    query.prepare(sql);
    if (!QueryRun(query, "查询info表"))
    {
        return;
    }
    if (query.first())
    {
        map.insert("temp_w", query.value(0).toInt());
        map.insert("temp_d", query.value(1).toInt());
        map.insert("pm10_w", query.value(2).toInt());
        map.insert("pm10_d", query.value(3).toInt());
        map.insert("pm25_w", query.value(4).toInt());
        map.insert("pm25_d", query.value(5).toInt());
        map.insert("so2_w", query.value(6).toInt());
        map.insert("so2_d", query.value(7).toInt());
        map.insert("quality_w", query.value(8).toInt());
        map.insert("quality_d", query.value(9).toInt());
    }
}

void Detail::dataUpdate()
{
    QSqlQuery query(*Conn());
    QString sql = "SELECT name, time FROM city LIMIT 8 OFFSET " + QString::number(page,10) + ";";
    query.prepare(sql);
    if (!QueryRun(query, "取7条数据在第"+QString::number(page,10)+"页"))
        return;
    else
    {
        for (int i = 0; i < 7; i ++)
        {
            if (query.next())
            {
//                qDebug()<<query.value(1);
                changeMgr(i, query.value(0).toString(), query.value(1).toString());
            }
            else
            {
                if (i == 0 && page >= 7)
                {
                    page -= 7;
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
    ui->pgdn->setEnabled(!isTail);
    ui->pgdn->setHidden(isTail);
    ui->pgup->setEnabled(!isHead);
    ui->pgup->setHidden(isHead);
}

void Detail::on_pgup_clicked()
{
    if (isTail)
        isTail = false;
    page -= 7;
    if (page == 0)
        isHead = true;
    dataUpdate();
}

void Detail::on_pgdn_clicked()
{
    if (isHead)
        isHead = false;
    page += 7;
    dataUpdate();
}

void Detail::changeMgr(int row, QString name, QString time)
{
    QDateTime dtime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    switch (row) {
    case 0:
        if (name == "")
        {
            ui->city_1->hide();
            ui->time_1->hide();
        }
        else
        {
            ui->city_1->show();
            ui->city_1->setText(name);
            ui->time_1->show();
            ui->time_1->setText(getTime(dtime));
        }
        break;
    case 1:
        if (name == "")
        {
            ui->city_2->hide();
            ui->time_2->hide();
        }
        else
        {
            ui->city_2->show();
            ui->city_2->setText(name);
            ui->time_2->show();
            ui->time_2->setText(getTime(dtime));
        }
        break;
    case 2:
        if (name == "")
        {
            ui->city_3->hide();
            ui->time_3->hide();
        }
        else
        {
            ui->city_3->show();
            ui->city_3->setText(name);
            ui->time_3->show();
            ui->time_3->setText(getTime(dtime));
        }
        break;
    case 3:
        if (name == "")
        {
            ui->city_4->hide();
            ui->time_4->hide();
        }
        else
        {
            ui->city_4->show();
            ui->city_4->setText(name);
            ui->time_4->show();
            ui->time_4->setText(getTime(dtime));
        }
        break;
    case 4:
        if (name == "")
        {
            ui->city_5->hide();
            ui->time_5->hide();
        }
        else
        {
            ui->city_5->show();
            ui->city_5->setText(name);
            ui->time_5->show();
            ui->time_5->setText(getTime(dtime));
        }
        break;
    case 5:
        if (name == "")
        {
            ui->city_6->hide();
            ui->time_6->hide();
        }
        else
        {
            ui->city_6->show();
            ui->city_6->setText(name);
            ui->time_6->show();
            ui->time_6->setText(getTime(dtime));
        }
        break;
    case 6:
        if (name == "")
        {
            ui->city_7->hide();
            ui->time_7->hide();
        }
        else
        {
            ui->city_7->show();
            ui->city_7->setText(name);
            ui->time_7->show();
            ui->time_7->setText(getTime(dtime));
        }
        break;
    }
}

QString Detail::getTime(QDateTime dtime)
{
    qint64 time = dtime.msecsTo(QDateTime::currentDateTime());
    if (time < 3600000)
        return "1小时内";
    else if (time <  86400000)
        return tr("%1小时前").arg(time/3600000);
    else
        return tr("%1天前").arg(time/86400000);
}

void Detail::_Chg_Value(QString city)
{
    QString sql = "SELECT temp, pm10, pm25, so2, quality, time FROM city WHERE name='%1'";
    QSqlQuery query(*Conn());
    query.prepare(sql.arg(city));
    if (!QueryRun(query, tr("查找城市%1的数据").arg(city)))
        return;
    if (query.next())
    {
        int temp = query.value(0).toInt();
        ChgColor("temp", temp);
        int pm10 = query.value(1).toInt();
        ChgColor("pm10", pm10);
        int pm25 = query.value(2).toInt();
        ChgColor("pm25", pm25);
        int so2 = query.value(3).toInt();
        ChgColor("so2", so2);
        int quality = query.value(4).toInt();
        ChgColor("quality", quality);

        ui->temp_v->setText(QString::number(temp));
        ui->pm10_v->setText(QString::number(pm10));
        ui->pm25_v->setText(QString::number(pm25));
        ui->so2_v->setText(QString::number(so2));
        ui->quality_v->setText(QString::number(quality));
        ui->name->setText(city);
        ui->c_time->setText(query.value(5).toString());

        QPropertyAnimation* _temp = new QPropertyAnimation(ui->temp, "value");
        _temp->setDuration(1000);
        _temp->setStartValue(-20);
        _temp->setEndValue(temp);
        QPropertyAnimation* _pm10 = new QPropertyAnimation(ui->pm10, "value");
        _pm10->setDuration(1000);
        _pm10->setStartValue(0);
        _pm10->setEndValue(pm10);
        QPropertyAnimation* _pm25 = new QPropertyAnimation(ui->pm25, "value");
        _pm25->setDuration(1000);
        _pm25->setStartValue(0);
        _pm25->setEndValue(pm25);
        QPropertyAnimation* _so2 = new QPropertyAnimation(ui->so2, "value");
        _so2->setDuration(1000);
        _so2->setStartValue(0);
        _so2->setEndValue(so2);
        QPropertyAnimation* _quality = new QPropertyAnimation(ui->quality, "value");
        _quality->setDuration(1000);
        _quality->setStartValue(0);
        _quality->setEndValue(quality);

        _temp->start();
        _pm10->start();
        _pm25->start();
        _so2->start();
        _quality->start();
    }

}

void Detail::ChgColor(QString v_name, int value)
{
    QString qss = this->qss;
    QString qss_t = "#%1:chunk{border:1px;background-color:%2;}";
    QString v_temp = v_name + "_%1";
    qss_t = qss_t.arg(v_name);
    int tmp1 = map[v_temp.arg("w")];
    int tmp2 = map[v_temp.arg("d")];

    if (v_name == "temp")
    {
        if (value <= tmp1 || value >= tmp2)
            qss += qss_t.arg("red");
        else
            qss += qss_t.arg("green");
    }
    else
    {
        if (value >= tmp1 && value < tmp2)
            qss += qss_t.arg("yellow");
        else if (value >= tmp2)
            qss += qss_t.arg("red");
        else
            qss += qss_t.arg("green");
    }
    this->qss = qss;
    setStyleSheet(this->qss);
}

void Detail::_InitTable(int b)
{
    this->back = b;
    dataUpdate();
    if (b != 2)
        _Chg_Value(ui->city_1->text());
}

void Detail::on_city_1_clicked()
{
    _Chg_Value(ui->city_1->text());
}

void Detail::on_city_2_clicked()
{
    _Chg_Value(ui->city_2->text());
}

void Detail::on_city_3_clicked()
{
    _Chg_Value(ui->city_3->text());
}

void Detail::on_city_4_clicked()
{
    _Chg_Value(ui->city_4->text());
}

void Detail::on_city_5_clicked()
{
    _Chg_Value(ui->city_5->text());
}

void Detail::on_city_6_clicked()
{
    _Chg_Value(ui->city_6->text());
}

void Detail::on_city_7_clicked()
{
    _Chg_Value(ui->city_7->text());
}

void Detail::on_back_clicked()
{
    emit display(this->back);
    this->page = 0;
    if (isTail)
        isTail = false;
    if (!isHead)
        isHead = true;
}
