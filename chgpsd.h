#ifndef CHGPSD_H
#define CHGPSD_H

#include <QDialog>

namespace Ui {
class ChgPsd;
}

class ChgPsd : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChgPsd(QString name,QWidget *parent = 0);
    ~ChgPsd();
    
private slots:
    void on_submit_clicked();

private:
    Ui::ChgPsd *ui;
    QString name;
};

#endif // CHGPSD_H
