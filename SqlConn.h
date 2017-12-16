#ifndef SQLCONN_H
#define SQLCONN_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

QSqlDatabase* Conn()
{
    QSqlDatabase* database = NULL;
//    判断是否存在一个名为one_conn的连接,
//    Qt默认的连接名是qt_sql_default_connection
    if(QSqlDatabase::contains("one_conn"))
    {
//        存在就直接返回该链接
        database = new QSqlDatabase(QSqlDatabase::database("one_conn"));
    }
    else
    {
//        不存在就新建一个名为one_conn的连接
//        如果不指定第二个参数，那么就会使用上边默认的连接名
        database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "one_conn"));
//        新建或者打开一个名为MyDatabase.db的数据库文件
        database->setDatabaseName("MyDatabase.db");
        database->setUserName("dgyang");
        database->setPassword("1995");
    }
    return database;
}

void InitSql()
{
    QSqlDatabase* database = Conn();
    if (!database->open())
    {
        qDebug()<<"open failed!"<<database->lastError();
    }
    else
    {
        qDebug()<<"Open success!";
    }
    QString sql = "create table student(id int primary key, name varchar(30), age int)";
    QSqlQuery query(*database);
    query.prepare(sql);
    if (!query.exec())
    {
        qDebug()<<"Error:"<<query.lastError();
    }
    else
    {
        qDebug()<<"Create Success!";
    }
}

#endif // SQLCONN_H
