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
    explicit Control(QWidget *parent = 0);
    ~Control();
    
private:
    Ui::Control *ui;
    void InitWindow();
    MyMessageBox* message;

public slots:
    void showUser(QString);

signals:

private slots:
    void on_user_clicked();

    void recvMsg(char*);

    void timeUpdate();
};

#endif // CONTROL_H
