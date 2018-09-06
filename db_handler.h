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
    bool has_img_list();
    bool has_tags_list();
    void create_img_list();
    void create_tags_list();
    bool check_exist_img(const QString& path);
    bool check_exist_tag(const QString& tag);
public:
    db_handler();

    bool check_insert_path(const QString& path);
    bool check_insert_tag(const QString& tag);
    void get_all_path(QList<QString> *path_walker_album_list);
    QList<QString> get_all_tag();
    QString get_tags(const QString& path);
    bool set_tags(const QString& path, const QString& tags);
    void get_by_tags(QList<QString> *path_walker_album_list, QString tags);
    // debug test
    void show_all_rec();
};


#endif // DB_HANDLER_H
