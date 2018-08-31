#include "path_walker.h"
#include <QDebug>
path_walker::path_walker()
{

}

void path_walker::current_files(QString path)
{
    /*
     * func: 产生图片集,
     * args: path 有文件的文件夹路径
     * returns: 图片(jpg,png,gif)的列表,注意查询是否为空列表!
     */
    this->current_list.clear();
    QDir dir_files(path);
    dir_files.setFilter(QDir::Files|QDir::Hidden);
    dir_files.setSorting(QDir::Name);
    dir_files.sorting();
    const QFileInfoList path_list = dir_files.entryInfoList();
    QFileInfoList::const_iterator iter = path_list.begin();
    while(iter != path_list.end())
    {
        // 判断文件类型
        if((*iter).suffix() == QString("jpg") ||
                (*iter).suffix() == QString("JPG")||
                (*iter).suffix() == QString("png")||
                (*iter).suffix() == QString("PNG")||
                (*iter).suffix() == QString("gif")||
                (*iter).suffix() == QString("GIF")
                ){
            this->current_list.append((*iter).filePath());
        }
        iter++;
    }
}

void path_walker::walk_path(QString root, bool is_first_time)
{
    /* func: list all path with pictures
     * args: root
     * return: list of path
     */
    if(is_first_time){
        // 当迭代调用开始时，清空列表
        this->all_paths.clear();
        // 重置计数器
        this->index = -1;
    }
    QDir dirs(root);
    dirs.setFilter(QDir::Files|QDir::Hidden);
    dirs.setSorting(QDir::Name);
    dirs.sorting();
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

QList<QString>* path_walker::get_img_grp(int dirct)
{
    if(dirct == PREVIOUS){
        if(this->index>0)
            this->index--;
        else{
            return nullptr;
        }
    }else{
        if(this->index<this->all_paths.length()-1)
            this->index++;
        else{
            return nullptr;
        }
    }
    qDebug()<<this->all_paths[this->index];
    current_files(this->all_paths[this->index]);
    return &this->current_list;
}


// debug ...
void path_walker::show_paths()
{
    for(int i=0;i<this->all_paths.length();i++){
        qDebug()<<all_paths[i];
    }

}

