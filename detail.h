#ifndef DETAIL_H
#define DETAIL_H

#include <QDialog>
#include <QHash>

namespace Ui {
class Detail;
}

class QDateTime;

class Detail : public QDialog
{
    Q_OBJECT
    
public:
    explicit Detail(QWidget *mainW, QWidget *parent = 0);
    ~Detail();
protected:
    void changeMgr(int, QString, QString);

    QString getTime(QDateTime);

    void ChgColor(QString, int);

protected slots:
    void _Chg_Value(QString);

    void _InitTable(int);

    void dataUpdate();

    void _InitMap();

private slots:
    void on_pgup_clicked();

    void on_pgdn_clicked();

    void on_city_1_clicked();

    void on_city_2_clicked();

    void on_city_3_clicked();

    void on_city_4_clicked();

    void on_city_5_clicked();

    void on_city_6_clicked();

    void on_city_7_clicked();

    void on_back_clicked();

signals:
    void display(int);

private:
    Ui::Detail *ui;
    QString qss;
    int back;

    bool isTail;
    bool isHead;
    int page;

    QHash<QString, int> map;
};

#endif // DETAIL_H
