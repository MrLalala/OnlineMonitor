#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <QLabel>

class ErrorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ErrorLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~ErrorLabel(){}
signals:
    
public slots:
    
};

#endif // ERRORLABEL_H
