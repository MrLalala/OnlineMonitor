#ifndef REGISTERW_H
#define REGISTERW_H

#include <QDialog>

class MyMessageBox;

namespace Ui {
class RegisterW;
}

class RegisterW : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegisterW(QWidget *mainW, QWidget *parent = 0);
    ~RegisterW();

public slots:
    void onEnter();

    void clearMsg();

private slots:
    void on_back_clicked();

    void on_regist_clicked();

    void msgRecv(char*);

private:
    Ui::RegisterW *ui;
    MyMessageBox* temp;

signals:
    void display(int);
    void userLogin(QString);
    void closeW();
};

#endif // REGISTERW_H
