#include "registerw.h"
#include "ui_registerw.h"
#include "SqlConn.h"
#include "maincontrol.h"
#include "mymessagebox.h"
#include "json.h"

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
    clearMsg();
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
            sql = "INSERT INTO user(name, password, permission) VALUES ('" + name + "','" + psd + "', 3)";
            query.prepare(sql);
            if (!QueryRun(query, "插入注册用户."))
            {
                return;
            }
            else
            {
                temp = new MyMessageBox("登录确认", "是否直接登录？","query");
                connect(temp, SIGNAL(sendMsg(char*)),SLOT(msgRecv(char*)));
                temp->setModal(true);
                temp->show();
            }

        }
        else
        {
            ui->name_error->setText("该用户名已存在！");
            return;
        }
    }
}

void RegisterW::onEnter()
{
    on_regist_clicked();
}

void RegisterW::msgRecv(char *msg)
{
    cJSON* root = cJSON_Parse(msg);
    cJSON* type = cJSON_GetObjectItem(root, "type");
    if (QString(type->valuestring) == "yes")
    {
        MainControl* c = new MainControl;
        connect(this,SIGNAL(userLogin(QString)),c,SLOT(getName(QString)));
        c->show();
        emit userLogin(ui->name->text());
        emit closeW();
        this->close();
        temp->close();
    }
    else
    {
        on_back_clicked();
        temp->close();
    }
}

void RegisterW::clearMsg()
{
    ui->name->clear();
    ui->name_error->clear();
    ui->psd->clear();
    ui->psd_error->clear();
    ui->repsd->clear();
    ui->repsd_error->clear();
}
