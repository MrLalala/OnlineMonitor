#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyMessageBox(QString title = "消息",QString msg = "提示", QString type = "ok", QString yes = "是", QString no = "否", QWidget *parent = 0);
    ~MyMessageBox();
    
signals:
    void sendMsg(char*);
private slots:
    void on_yes_clicked();

    void on_no_clicked();

private:
    Ui::MyMessageBox *ui;
    QString msg;
};

#endif // MYMESSAGEBOX_H
