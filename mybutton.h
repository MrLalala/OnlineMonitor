#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
    ~MyButton(){return;}
signals:
    
public slots:

private:
    QString qss;
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    
};

#endif // MYBUTTON_H
