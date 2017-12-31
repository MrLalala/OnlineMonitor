#include "mybutton.h"

MyButton::MyButton(QWidget *parent) :
    QPushButton(parent)
{
    qss = "MyButton{background: transparent;color: %1;}";
    setStyleSheet(qss.arg("white"));
}

void MyButton::enterEvent(QEvent *)
{
    setStyleSheet(qss.arg("white;text-decoration:underline;"));
}

void MyButton::leaveEvent(QEvent *)
{
    setStyleSheet(qss.arg("white"));
}
