#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    ~MyButton(){return;}
protected:

signals:
    
public slots:

private:
    QString qss;
    
};

#endif // MYBUTTON_H
