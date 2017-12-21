#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    
public:
    explicit Login(QWidget* mainW, QWidget *parent = 0);
    ~Login();
    
protected:
//    void keyReleaseEvent(QKeyEvent *);

private slots:
    void on_login_clicked();

    void on_signin_clicked();

    void on_about_clicked();

    void on_exit_clicked();

private:
    Ui::Login *ui;


signals:
    void display(int);
    void closeW();
};

#endif // LOGIN_H
