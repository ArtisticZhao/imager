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

class path_walker
{
private:
    QList<QString> album_paths;
    QList<QString> current_album_files;
    bool has_image(const QFileInfoList* qfl);
public:
    path_walker();
    // 返回图片集
    const QList<QString>* current_files(QString path);
    // 迭代查询数据, 数据将被保存在all_paths中
    void walk_path(QString root, bool is_first_time=false);
    // 得到列表
    const QList<QString>* get_all_albums();
    // debug
    void show_paths();
};

#endif // PATH_WALKER_H
