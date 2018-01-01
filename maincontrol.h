#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QDialog>

class MyMessageBox;
class Control;
class QStackedLayout;
class PeopleMgr;
class QPoint;

namespace Ui {
class MainControl;
}

class MainControl : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainControl(QWidget *parent = 0);
    ~MainControl();
    
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::MainControl *ui;
    MyMessageBox* msgBox;

    Control* control;
    PeopleMgr* pMgr;
    QStackedLayout* stackLayout;

    QString user;
    bool mousePressed;
    QPoint mousePos;

public slots:
    void getName(QString);
//    void _recvDisplay(int);

signals:
    void sendName(QString);
};

#endif // MAINCONTROL_H
