#include "db_handler.h"
#include <QDebug>

db_handler::db_handler()
{
    this->database.setDatabaseName("database.db");
    if(database.open()){
        qDebug()<<"Database Opened";
    }else{
        qDebug()<<"Database Open Failed";
    }
    if(!this->has_database()){
        // 不存在存在数据库了
        this->init_database();
    }
}

bool db_handler::has_database()
{
    QSqlQuery sql_query;
    bool is_table_exist = database.tables().contains(QLatin1String("img_list"));
    qDebug()<<"check database exist: "<<is_table_exist;
    return is_table_exist;
}

void db_handler::init_database()
{
    /**
     * 初始化数据库,如果数据库不存在,则建立数据库,并创建数据表
     * */
    QSqlQuery sql_query;
    sql_query.prepare("create table img_list (path varchar(200) primary key, title text, tags text, visit_times int)");
    if(!sql_query.exec()){
        qDebug()<<"Table Create failed";
        qDebug()<<sql_query.lastError();
    }else{
        qDebug()<<"Table Create success";
    }
}

bool db_handler::check_exist(const QString &path)
{
    bool exists = false;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT path FROM img_list WHERE path = (:path)");
    checkQuery.bindValue(":path", path);

    if (checkQuery.exec()){
        if (checkQuery.next()){
            exists = true;
        }
    }else{
        qDebug() << "check exists failed: " << checkQuery.lastError();
    }
    return exists;
}

bool db_handler::check_insert(const QString& path)
{
    bool success = false;
    QSqlQuery query;
    if(!this->check_exist(path)){
        // insert
        query.prepare("INSERT INTO img_list (path) VALUES (:path)");
        query.bindValue(":path", path);
        if(query.exec()){
           success = true;
        }
        else{
            qDebug() << "insert error:  "
                     << query.lastError();
        }
    }else{
        qDebug() << "path already exist!";
    }

    return success;
}

void db_handler::get_all_path(QList<QString> *path_walker_album_list)
{
    path_walker_album_list->clear();
    QSqlQuery query;
    query.prepare("SELECT path FROM img_list");
    if(query.exec()){
        while(query.next()){
            path_walker_album_list->append(query.value(0).toString());
        }
    }else{
        qDebug() << "insert error:  "
                 << query.lastError();
    }
}

QString db_handler::get_tags(const QString &path)
{
    QSqlQuery query;
    query.prepare("SELECT tags FROM img_list WHERE path = (:path)");
    query.bindValue(":path", path);
    if(query.exec()){
        if(query.next()){
            return query.value(0).toString();
        }
    }
    else{
        qDebug() << "insert error:  "
                 << query.lastError();
    }

    return "";
}

bool db_handler::set_tags(const QString &path, const QString &tags)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE img_list SET tags = (:tags) WHERE path = (:path)");
    query.bindValue(":path", path);
    query.bindValue(":tags", tags);
    if(query.exec()){
       success = true;
    }
    else{
        qDebug() << "insert error:  "
                 << query.lastError();
    }
    return  success;
}

void db_handler::get_by_tags(QList<QString> *path_walker_album_list, QString tags)
{
    QStringList tag_list=tags.split(",");
    qDebug()<<tag_list;
    if(tag_list.length()>0){
        // 如果tag_list 包含结果, 结果按照 'and' 关系 进行查询!
        path_walker_album_list->clear();
        QSqlQuery query;
        QString query_str = "SELECT path from img_list WHERE tags LIKE '%%1%'";
        QString add_str = " and tags LIKE '%%1%'";
        query_str = query_str.arg(tag_list.at(0));
        // 拼接字符串
        for(int i=1;i<tag_list.length();i++){
            query_str += add_str.arg(tag_list.at(i));
        }
        qDebug()<<query_str;
        query.prepare(query_str);
        if(query.exec()){
            while(query.next()){
                path_walker_album_list->append(query.value(0).toString());
            }
        }
    }else{
        // 如果列表为空则返回全部数据库结果
        this->get_all_path(path_walker_album_list);
    }

}

void db_handler::show_all_rec()
{
    QSqlQuery sql_query;
    sql_query.prepare("select * from img_list");
    if(!sql_query.exec())
    {
       qDebug()<<sql_query.lastError();
    }
    else
    {
       while(sql_query.next())
       {
           QString path = sql_query.value(0).toString();
           QString title = sql_query.value(1).toString();
           QString tags = sql_query.value(2).toString();
           int visit_times = sql_query.value(3).toInt();
           qDebug()<<QString("path:%1  title:%2  tags:%3  visit times:%4").arg(path).arg(title).arg(tags).arg(visit_times);
       }
    }
}
