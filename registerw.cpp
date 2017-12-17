#include "registerw.h"
#include "ui_registerw.h"

RegisterW::RegisterW(QWidget* mainW, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterW)
{
    ui->setupUi(this);
    installEventFilter(mainW);
}

RegisterW::~RegisterW()
{
    delete ui;
}

void RegisterW::on_back_clicked()
{
    ui->name->clear();
    ui->name_error->clear();
    ui->psd->clear();
    ui->psd_error->clear();
    ui->repsd->clear();
    ui->repsd_error->clear();
    emit display(0);
}
