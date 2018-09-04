#ifndef DB_HANDLER_H
#define DB_HANDLER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class db_handler
{
private:
    // use Sqlite database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    // 检测是否存在数据库
    bool has_database();
    void init_database();
    bool check_exist(const QString& path);
public:
    db_handler();

    bool check_insert(const QString& path);
    void get_all_path(QList<QString> *path_walker_album_list);
    QString get_tags(const QString& path);
    bool set_tags(const QString& path, const QString& tags);
    void get_by_tags(QList<QString> *path_walker_album_list, QString tags);
    // debug test
    void show_all_rec();
};


#endif // DB_HANDLER_H
