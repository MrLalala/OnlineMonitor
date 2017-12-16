#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>

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
};

#endif // CONTROL_H
