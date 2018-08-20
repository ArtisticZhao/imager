#ifndef PATH_WALKER_H
#define PATH_WALKER_H

/*
 * 本类用于产生图片列表,
 * 程序认为: 如果一个文件夹下如果有图片文件则这个文件夹就是一个图片集,
 * 则在 all_paths 中存储当前的路径,
 * 本类将来应该能够扩展数据库的功能.
 */

#include <QDir>

#define PREVIOUS 0
#define NEXT 1

class path_walker
{
private:
    QString current_path;
    QList<QString> all_paths;

    int index=-1;
public:
    QList<QString> current_list;
    path_walker();
    // 产生图片集
    void current_files(QString path);
    // 迭代查询数据
    void walk_path(QString root);
    // 得到列表
    QList<QString>* get_img_grp(int);
    // debug
    void show_paths();
};

#endif // PATH_WALKER_H
