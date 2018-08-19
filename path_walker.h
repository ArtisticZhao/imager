#ifndef PATH_WALKER_H
#define PATH_WALKER_H
#include <QDir>


class path_walker
{
private:
    QString current_path;
    QList<QString> all_paths;
public:
    path_walker();
    // for debug
    void find_dir(QString path);
    QList<QString> current_files(QString path);
    void walk_path(QString root);
    // debug
    void show_paths();
};

#endif // PATH_WALKER_H
