#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>

class MyMessageBox;

namespace Ui {
class Control;
}

class Control : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Control(QWidget *mainW, QWidget *parent = 0);
    ~Control();
    
private:
    Ui::Control *ui;
    MyMessageBox* message;
    QString name;

public slots:
    void showUser(QString);

signals:
    void closeW();

    void display(int);

    void send_back(int);

private slots:
    void on_user_clicked();

    void recvMsg(char*);

    void timeUpdate();
    void on_exit_clicked();
    void on_psdChg_clicked();
    void on_userMgr_clicked();

    void on_cityMgr_clicked();

    void on_showData_clicked();

protected:
    void keyReleaseEvent(QKeyEvent *);
};

#endif // CONTROL_H
