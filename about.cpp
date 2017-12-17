#include "about.h"
#include "ui_about.h"

About::About(QWidget* mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    installEventFilter(mainW);
}

About::~About()
{
    delete ui;
}

void About::on_toolButton_clicked()
{
    emit display(0);
}
