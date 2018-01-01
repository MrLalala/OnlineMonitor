#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QDialog>
#include "json.h"

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyMessageBox(QString title = "消息",QString msg = "提示", QString type = "ok", QString flag = "", QString yes = "是", QString no = "否", QWidget *parent = 0);
//    static bool query();
//    static bool warn();
//    static bool error();
//    static bool ok();
    ~MyMessageBox();
    
signals:
    void sendMsg(char*);
private slots:
    void on_yes_clicked();

    void on_no_clicked();

private:
    Ui::MyMessageBox *ui;
    QString msg;
    cJSON* root;
};

#endif // MYMESSAGEBOX_H
