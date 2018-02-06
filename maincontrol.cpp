#include "maincontrol.h"
#include "ui_maincontrol.h"
#include "control.h"
#include "peoplemgr.h"
#include "citymgr.h"
#include "detail.h"
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
    QString qss = QString("#MainControl{border-image: url(:/images/main2.jpg);}");
    qss += "QToolButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;}";
    qss += "#time{color:white;font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "QPushButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;font-family:Microsoft YaHei UI; font-size: 15px;}";
    qss += "#user_1,#user_2,#user_3,#user_4{color:white;font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "QLabel {color:white;font-family: Microsoft YaHei UI;}";
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setStyleSheet(qss);

    control = new Control(this);
    pMgr = new PeopleMgr(this);
    cMgr = new CityMgr(this);
    detail = new Detail(this);
    stackLayout = new QStackedLayout(this);
    stackLayout->addWidget(control);
    stackLayout->addWidget(pMgr);
    stackLayout->addWidget(cMgr);
    stackLayout->addWidget(detail);

    connect(this, SIGNAL(sendName(QString)), control, SLOT(showUser(QString)));
    connect(control,SIGNAL(display(int)),stackLayout,SLOT(setCurrentIndex(int)));
    connect(pMgr, SIGNAL(display(int)),stackLayout, SLOT(setCurrentIndex(int)));
    connect(cMgr, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));
    connect(detail, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));
    connect(control, SIGNAL(closeW()),this, SLOT(close()));
    connect(control, SIGNAL(send_back(int)), detail, SLOT(_InitTable(int)));
    connect(cMgr, SIGNAL(select_city(QString)), detail, SLOT(_Chg_Value(QString)));
    connect(cMgr, SIGNAL(send_back(int)), detail, SLOT(_InitTable(int)));
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

//void MainControl::_recvDisplay(int layer)
//{
//    Q_UNUSED(layer);
//}
