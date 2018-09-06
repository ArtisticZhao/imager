#include "path_walker.h"

bool path_walker::has_image(const QFileInfoList *qfl)
{
    /**
     * 判断是否存在图片格式
     */
    QFileInfoList::const_iterator iter = qfl->begin();
    while(iter != qfl->end())
    {
        // 判断文件类型
        if((*iter).suffix() == QString("jpg") ||
                (*iter).suffix() == QString("JPG")||
                (*iter).suffix() == QString("png")||
                (*iter).suffix() == QString("PNG")||
                (*iter).suffix() == QString("gif")||
                (*iter).suffix() == QString("GIF")
                ){
            return true;
        }
        iter++;
    }
    return false;
}

path_walker::path_walker()
{

}

const QList<QString> *path_walker::current_files(QString path)
{
    /*
     * func: 产生图片集,
     * args: path 有文件的文件夹路径
     * returns: 图片(jpg,png,gif)的列表,注意查询是否为空列表!
     */
    this->current_album_files.clear();
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
            this->current_album_files.append((*iter).filePath());
        }
        iter++;
    }
    return &this->current_album_files;
}

void path_walker::walk_path(QString root, bool is_first_time)
{
    /* func: list all path with pictures
     * args: root
     * return: list of path
     */
    if(is_first_time){
        // 当迭代调用开始时，清空列表
        this->album_paths.clear();
    }
    QDir dirs(root);
    dirs.setFilter(QDir::Files|QDir::Hidden);
    dirs.setSorting(QDir::Name);
    dirs.sorting();
    const QFileInfoList file_list = dirs.entryInfoList();
    if(file_list.length()>0)
    {
        // exist files
        if(this->has_image(&file_list)){
            // exist image file type
            this->album_paths.append(root);
        }
    }
    dirs.setFilter(QDir::Dirs|QDir::Hidden);
    const QFileInfoList path_list = dirs.entryInfoList();
    if(path_list.length()>2)
    {
        // exist dirs
        QFileInfoList::const_iterator iter = path_list.begin();
        while(iter != path_list.end()){
            //排除 .和..
            if((*iter).fileName() == "." || (*iter).fileName() == "..")
            {
                iter++;
                continue;
            }
            this->walk_path((*iter).filePath());
            iter++;
        }
    }

}

void path_walker::load_all_from_database()
{
    this->db.get_all_path(&this->album_paths);
}

const QList<QString> *path_walker::get_all_albums()
{
    return &this->album_paths;
}

QList<QString> path_walker::get_all_tags()
{
    return this->db.get_all_tag();
}

void path_walker::save_albums()
{
    for(int i=0;i<this->album_paths.length();i++){
        this->db.check_insert_path(this->album_paths.at(i));
    }
}

QString path_walker::get_tags(const QString &path)
{
    return this->db.get_tags(path);
}

void path_walker::save_tags(const QString &path, const QString &tags)
{
    // save to img_list
    this->db.set_tags(path, tags);
    // save to tags_list
    QStringList tag_list=tags.split(",");
    for(int i=0;i<tag_list.length();i++){
        this->db.check_insert_tag(tag_list.at(i));
    }
}

void path_walker::get_by_tags(const QString &tags)
{
    this->db.get_by_tags(&this->album_paths, tags);
}



// debug ...
void path_walker::show_paths()
{
    for(int i=0;i<this->album_paths.length();i++){
        qDebug()<<album_paths[i];
    }

}
