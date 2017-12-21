#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "login.h"
#include "registerw.h"
#include "about.h"
#include <QStackedLayout>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
//    去除窗体边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
//    设置自动填充的背景
    QString qss = "QDialog{border-image: url(:/images/main2.jpg);}";
//    设置按钮、输入框透明
    qss += "QToolButton,QLineEdit{font-family: Microsoft YaHei UI; font-size: 15px;color: white;background-color: rgba(0,0,0,0);}";
//    设置QLabel字体颜色为白色
    qss += "QLabel{color:white; font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "ErrorLabel{color:red; font-family: Microsoft YaHei UI; font-size: 15px;}";
    qss += "#welcome{color:white; font-family: Microsoft YaHei UI; font-size: 35px;}";
    setStyleSheet(qss);
    login = new Login(this);
    registerw = new RegisterW(this);
    about = new About(this);
    stackLayout = new QStackedLayout(this);
    stackLayout->addWidget(login);
    stackLayout->addWidget(registerw);
    stackLayout->addWidget(about);
    connect(login,SIGNAL(display(int)),SLOT(_recvDisplay(int)));
    connect(registerw,SIGNAL(display(int)),SLOT(_recvDisplay(int)));
    connect(about,SIGNAL(display(int)),SLOT(_recvDisplay(int)));
    connect(login,SIGNAL(closeW()),SLOT(close()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::_recvDisplay(int a)
{
    stacked = a;
    stackLayout->setCurrentIndex(a);
}

//过滤stackedLayout的esc按键事件。
bool MainWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == (QEvent::MouseButtonPress || QEvent::MouseButtonRelease||QEvent::MouseMove))
    {
        return true;
    }
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* temp = static_cast<QKeyEvent*>(event);
        qDebug()<<temp->key();
        if(temp->key() == Qt::Key_Escape)
        {
            if (obj == login)
            {
                this->close();
                login->close();
                return true;
            }
            else if (obj == registerw || obj == about)
            {
                stackLayout->setCurrentIndex(0);
                return true;
            }
        }
        return false;
    }
    else
//        不是这三个对象的直接交给父窗体处理处理
        return QObject::eventFilter(obj, event);
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed)
    {
        this->move(e->globalPos() - mousePos);
        e->accept();
    }
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePos = e->globalPos() - this->pos();
        e->accept();
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mousePressed = false;
    Q_UNUSED(e);
}
