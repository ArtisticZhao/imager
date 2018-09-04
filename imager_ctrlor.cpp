#include "imager_ctrlor.h"
#include <QDebug>
bool imager_ctrlor::set_img_list(int direct)
{
    bool is_success = true;
    if(direct==PREVIOUS){
        // 设置当前目录到上一个相册
        if(this->album_index > 0){
            this->album_index--;
        }else
            is_success = false;
    }else{
        // 设置当前目录到下一个相册
        if(this->album_index < this->album_len - 1){
            this->album_index++;
        }else
            is_success = false;
    }
    if(is_success){
        this->current_img_list = this->pw->current_files(this->album_paths->at(this->album_index));
        this->current_len = this->current_img_list->length();
        // 以目录名作为相册名字
        this->album_name = this->album_paths->at(this->album_index).mid(this->album_paths->at(this->album_index).lastIndexOf('/')+1);
    }
    return is_success;
}

imager_ctrlor::imager_ctrlor(path_walker *pw)
{
    this->pw = pw;
}

void imager_ctrlor::init_imager_ctrlor()
{
    this->album_paths = this->pw->get_all_albums();
    this->album_len = this->album_paths->length();
    this->album_index = -1;
    this->img_index = -1;
    this->set_img_list(NEXT);
}

QString imager_ctrlor::get_album_name()
{
    return this->album_name;
}

bool imager_ctrlor::pre_album()
{
    this->img_index = -1;
    return this->set_img_list(PREVIOUS);
}

bool imager_ctrlor::next_album()
{
    this->img_index = -1;
    return this->set_img_list(NEXT);
}


QString imager_ctrlor::next_pic()
{

    if(this->img_index < this->current_len-1){
        this->img_index++;
    }else{
        // 下一组
        if(this->set_img_list(NEXT))
            // 索引指向下一组的列表头
            img_index = 0;
        else{
            return QString("tail");
        }
    }
    qDebug()<<"album: "<<this->album_index+1<<"/"<<this->album_len;
    qDebug()<<"->"<<this->img_index+1<<"/"<<this->current_len;
    return (*this->current_img_list)[this->img_index];
}

QString imager_ctrlor::pre_pic()
{

    if(this->img_index > 0){
        this->img_index--;
    }else{
        // 上一组
        if(this->set_img_list(PREVIOUS))
            // 索引指向下一组的列表尾
            this->img_index = this->current_len-1;
        else{
            this->img_index=-1;
            return QString("head");
        }
    }
    qDebug()<<"album: "<<this->album_index+1<<"/"<<this->album_len;
    qDebug()<<"<-"<< this->img_index+1<<"/"<<this->current_len;
    return (*this->current_img_list)[this->img_index];
}

QString imager_ctrlor::get_current_path()
{
    return  this->album_paths->at(this->album_index);
}
