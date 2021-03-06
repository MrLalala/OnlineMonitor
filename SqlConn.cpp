#include "SqlConn.h"

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

//权限为4位，分别为人物管理权限，城市管理权限，城市查看权限，登录权限。
//分别使用8,4,2,1来表示。默认admin权限为15，新注册人物权限为3（2+1）。

bool QueryRun(QSqlQuery& query, const QString opt, const QString type)
{
    bool success = true;
    if (type == "normal")
    {
        if (!query.exec())
        {
            success =  false;
        }
    }
    if (type == "batch")
    {
        if (!query.execBatch())
        {
            success = false;
        }
    }
    if (!success)
    {
        qDebug()<<query.lastQuery();
        qDebug()<<"Error:"<<query.lastError()<<" in "<<opt;
    }
    return success;

}

bool InitTable()
{
    QSqlDatabase* database = Conn();
    if (!database->open())
    {
        qDebug()<<"Database open Error:"<<database->lastError();
        return false;
    }
    QSqlQuery query(*database);
    QString sql = "select * from user where name='admin';";
    query.prepare(sql);
    if (QueryRun(query, "Find admin"))
    {
        if (!query.next())
        {
            sql = "INSERT INTO user(name, password, permission) VALUES('admin', 'admin', 15);";
            query.prepare(sql);
            if (!QueryRun(query, "Insert admin"))
            {
                qDebug()<<"Error Init";
                return false;
            }
        }
    }
    else
    {
        sql = "CREATE TABLE user ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'name'  TEXT(20) NOT NULL,'password'  TEXT(20) NOT NULL,'permission'  INTEGER NOT NULL);";
        query.prepare(sql);
        if (!QueryRun(query, "Add Table"))
            return false;
        sql = "INSERT INTO user(name, password, permission) VALUES('admin', 'admin', 15);";
        query.prepare(sql);
        if (!QueryRun(query, "Inser admin"))
            return false;
    }
    sql = "select * from city";
    query.prepare(sql);
    if (!QueryRun(query, "Find city"))
    {
        sql = "CREATE TABLE city('id'  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'name'  TEXT NOT NULL,'temp'  INTEGER,'pm10'  INTEGER,'pm25'  INTEGER,'so2'  INTEGER,'quality'  INTEGER, 'time'  TEXT NOT NULL)";
        query.prepare(sql);
        if (!QueryRun(query, "Add City Table"))
            return false;
    }
    sql = "select * from info";
    query.prepare(sql);
    if (!QueryRun(query, "find info"))
    {
        sql = "CREATE TABLE info ( temp_w  INTEGER NOT NULL, temp_d  INTEGER NOT NULL,pm10_w  INTEGER NOT NULL,pm10_d  INTEGER NOT NULL,pm25_w  INTEGER NOT NULL,pm25_d  INTEGER NOT NULL,so2_w  INTEGER NOT NULL,so2_d  INTEGER NOT NULL,quality_w  INTEGER NOT NULL,quality_d  INTEGER NOT NULL)";
        query.prepare(sql);
        if (!QueryRun(query, "插入info表"))
        {
            return false;
        }
    }
    return true;
}
