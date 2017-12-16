#include "control.h"
#include "login.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    添加中文显示
    QTextCodec* codec = QTextCodec::codecForName("urf-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
//    Control w;
//    w.show();
    Login login;
    login.show();
    
    return a.exec();
}
