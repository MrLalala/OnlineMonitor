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
private slots:
    void on_user_clicked();

    void recvMsg(char*);

    void timeUpdate();
    void on_exit_clicked();
    void on_psdChg_clicked();
};

#endif // CONTROL_H
