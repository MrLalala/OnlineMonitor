#include "mybutton.h"

MyButton::MyButton(QWidget *parent) :
    QPushButton(parent)
{
    qss = "MyButton:!hover{background: transparent;color: black} MyButton:hover{background: transparent; color: blue; text-decoration: underline}";
    setStyleSheet(qss);
}
