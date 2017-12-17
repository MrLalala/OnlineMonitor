#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT
    
public:
    explicit About(QWidget *mainW, QWidget *parent = 0);
    ~About();
    
private:
    Ui::About *ui;

signals:
    void display(int);
private slots:
    void on_toolButton_clicked();
};

#endif // ABOUT_H
