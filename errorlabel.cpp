#include "errorlabel.h"

ErrorLabel::ErrorLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
    QString qss = "ErrorLabel{color:red; font-family: Microsoft YaHei UI; font-size: 15px;}";
    setStyleSheet(qss);
}
