#ifndef CITYMGR_H
#define CITYMGR_H

#include <QDialog>

namespace Ui {
class CityMgr;
}

class QDateTime;
class ChgValue;

class CityMgr : public QDialog
{
    Q_OBJECT
    
public:
    explicit CityMgr(QWidget *mainW, QWidget *parent = 0);
    ~CityMgr();

protected:
    void changeRow1(QString, QDateTime);
    void changeRow2(QString, QDateTime);
    void changeRow3(QString, QDateTime);
    void changeRow4(QString, QDateTime);
    void changeMgr(int, QString, QString);
    void showChg(int);
    void delCity(int);
    void showCity(int);
    QString getTime(QDateTime);
    
private slots:
    void on_pgdn_clicked();

    void on_pgup_clicked();

    void on_update_1_clicked();

    void on_update_2_clicked();

    void on_update_3_clicked();

    void on_update_4_clicked();

    void dataUpdate();

    void on_newC_clicked();

    void on_del_1_clicked();

    void on_del_2_clicked();

    void on_del_3_clicked();

    void on_del_4_clicked();

    void on_exit_clicked();

    void on_show_1_clicked();

    void on_show_2_clicked();

    void on_show_3_clicked();

    void on_show_4_clicked();

signals:
    void display(int);

    void send_back(int);

    void select_city(QString);

private:
    Ui::CityMgr *ui;
    int page;
    bool isHead;
    bool isTail;
    ChgValue* temp;
};

#endif // CITYMGR_H
