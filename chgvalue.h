#ifndef CHGVALUE_H
#define CHGVALUE_H

#include <QDialog>

namespace Ui {
class ChgValue;
}

class ChgValue : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChgValue(QString city, QWidget *parent = 0);
    ~ChgValue();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void doChg();

private:
    Ui::ChgValue *ui;
    QString city;
};

#endif // CHGVALUE_H
