#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDialog>

class Login;
class RegisterW;
class About;
class QStackedLayout;
class QPoint;

namespace Ui {
class MainWidget;
}

class MainWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
protected:

protected slots:
    void _recvDisplay(int);
    bool eventFilter(QObject *, QEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::MainWidget *ui;
    Login* login;
    RegisterW* registerw;
    About* about;
    QStackedLayout* stackLayout;
    int stacked;
    bool mousePressed;
    QPoint mousePos;
};

#endif // MAINWIDGET_H
