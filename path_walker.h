#ifndef PATH_WALKER_H
#define PATH_WALKER_H

/*
 * 本类用于产生图片列表,
 * 程序认为: 如果一个文件夹下如果有图片文件则这个文件夹就是一个图片集,
 * 则在 all_paths 中存储当前的路径,
 * 本类将来应该能够扩展数据库的功能.
 */

#include <QDir>
#include <QDebug>
#include "db_handler.h"

class path_walker
{
private:
    QList<QString> album_paths;
    QList<QString> current_album_files;
    db_handler db;
    bool has_image(const QFileInfoList* qfl);
public:
    path_walker();
    bool is_emtry();
    // 返回图片集
    const QList<QString>* current_files(QString path);
    // 迭代查询数据, 数据将被保存在all_paths中
    void walk_path(QString root, bool is_first_time=false);
    // 从数据库中读取全部结果
    void load_all_from_database();
    // 得到列表
    const QList<QString>* get_all_albums();
    // 得到全部标签
    QList<QString> get_all_tags();
    // 将当前扫描结果保存到数据库
    void save_albums();
    // 读取标签信息
    QString get_tags(const QString& path);
    // 变更标签信息
    void save_tags(const QString& path, const QString& tags);
    // 根据标签得到paths
    void get_by_tags(const QString& tags);
    // debug
    void show_paths();

};

#endif // PATH_WALKER_H
