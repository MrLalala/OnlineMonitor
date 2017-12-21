#include "registerw.h"
#include "ui_registerw.h"
#include "SqlConn.h"

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

void RegisterW::on_regist_clicked()
{
    ui->name_error->clear();
    ui->psd_error->clear();
    ui->repsd_error->clear();

    QString name = ui->name->text();
    QString psd = ui->psd->text();
    QString repsd = ui->repsd->text();

    bool flag = true;

    if (name == NULL)
    {
        ui->name_error->setText("请输入用户名！");
        flag = false;
    }
    if (psd == NULL)
    {
        ui->psd_error->setText("请输入密码！");
        flag = false;
    }
    if (repsd == NULL)
    {
        ui->repsd_error->setText("请输入确认密码！");
        flag = false;
    }
    if (flag)
    {
        QSqlDatabase* data = Conn();
        QSqlQuery query(*data);
        QString sql = "SELECT * FROM user WHERE name = '" + name + "'";
        query.prepare(sql);
        if (!QueryRun(query, "查找用户名是否存在."))
        {
            return;
        }
        if (!query.next())
        {
            if (psd != repsd)
            {
                ui->repsd_error->setText("两次密码不相同！");
                return;
            }
            sql = "INSERT INTO user(name, password, permission) VALUES ('" + name + "','" + psd + "', 2)";
            query.prepare(sql);
            if (!QueryRun(query, "插入注册用户."))
            {
                return;
            }
        }
        else
        {
            ui->name_error->setText("该用户名已存在！");
            return;
        }
    }
}
