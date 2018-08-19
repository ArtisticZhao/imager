#include "path_walker.h"
#include <QDebug>
path_walker::path_walker()
{

}

void path_walker::find_dir(QString path)
{
    QDir dir(path);
    dir.setFilter(QDir::Dirs|QDir::Hidden);
    const QFileInfoList path_list = dir.entryInfoList();
    QFileInfoList::const_iterator iter = path_list.begin();
    while(iter != path_list.end())
    {
        qDebug()<< (*iter).filePath();
        iter++;
    }

}

QList<QString> path_walker::current_files(QString path)
{

    QDir dir_files(path);
    dir_files.setFilter(QDir::Files|QDir::Hidden);
    QList<QString> paths;
    const QFileInfoList path_list = dir_files.entryInfoList();
    QFileInfoList::const_iterator iter = path_list.begin();
    while(iter != path_list.end())
    {
        if((*iter).suffix() == QString("jpg") ||
                (*iter).suffix() == QString("png")||
                (*iter).suffix() == QString("gif"))
        {
            paths.append((*iter).filePath());
            qDebug()<< (*iter).filePath();
        }
        iter++;
    }

    return paths;
}

void path_walker::walk_path(QString root)
{
    /* func: list all path with pictures
     * args: root
     * return: list of path
     */
    QDir dirs(root);
    dirs.setFilter(QDir::Files|QDir::Hidden);
    const QFileInfoList file_list = dirs.entryInfoList();
    if(file_list.length()>0)
    {
        // exist files
        this->all_paths.append(root);
    }
    dirs.setFilter(QDir::Dirs|QDir::Hidden);
    const QFileInfoList path_list = dirs.entryInfoList();
    if(path_list.length()>2)
    {
        // exist dirs
        QFileInfoList::const_iterator iter = path_list.begin();
        while(iter != path_list.end()){

            if((*iter).fileName() == "." || (*iter).fileName() == "..")
            {
                //排除 .和..
                iter++;
                continue;
            }
            this->walk_path( (*iter).filePath());
            iter++;
        }
    }

}

void path_walker::show_paths()
{
    for(int i=0;i<this->all_paths.length();i++){
        qDebug()<<all_paths[i];
    }

}

