#ifndef ADDCITY_H
#define ADDCITY_H

#include <QDialog>

namespace Ui {
class AddCity;
}

class AddCity : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddCity(QWidget *parent = 0);
    ~AddCity();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void onCrt();

private:
    Ui::AddCity *ui;
};

#endif // ADDCITY_H
