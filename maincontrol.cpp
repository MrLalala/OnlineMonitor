#include "maincontrol.h"
#include "ui_maincontrol.h"
#include "control.h"
#include <QStackedLayout>
#include "mymessagebox.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>


MainControl::MainControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainControl)
{
    ui->setupUi(this);
    QString qss = QString("#MainControl,#Control{border-image: url(:/images/main2.jpg);}");
    qss += "QToolButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;}";
    qss += "MyButton{color:black;font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "#time{color:white;font-family: Microsoft YaHei UI; font-size: 15px;}";
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setStyleSheet(qss);
    control = new Control(this);
    stackLayout = new QStackedLayout(this);
    stackLayout->addWidget(control);

    connect(this, SIGNAL(sendName(QString)), control, SLOT(showUser(QString)));
    connect(control, SIGNAL(closeW()),SLOT(close()));
}

MainControl::~MainControl()
{
    delete ui;
}

bool MainControl::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == (QEvent::MouseButtonPress || QEvent::MouseButtonRelease || QEvent::MouseMove))
    {
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void MainControl::keyReleaseEvent(QKeyEvent *)
{

}

void MainControl::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed)
    {
        this->move(e->globalPos() - mousePos);
        e->accept();
    }
}

void MainControl::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePos = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainControl::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void MainControl::getName(QString s)
{
    user = s;
    emit sendName(s);
}
