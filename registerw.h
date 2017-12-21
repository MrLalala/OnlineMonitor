#ifndef REGISTERW_H
#define REGISTERW_H

#include <QDialog>

namespace Ui {
class RegisterW;
}

class RegisterW : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegisterW(QWidget *mainW, QWidget *parent = 0);
    ~RegisterW();
    
private slots:
    void on_back_clicked();

    void on_regist_clicked();

private:
    Ui::RegisterW *ui;

signals:
    void display(int);
};

#endif // REGISTERW_H
