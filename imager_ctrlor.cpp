#include "imager_ctrlor.h"
#include <QDebug>
imager_ctrlor::imager_ctrlor(path_walker *pw)
{
    this->pw = pw;
    this->set_img_list(pw->get_img_grp(NEXT));
}

bool imager_ctrlor::set_img_list(QList<QString> *list)
{
    /**
      * set ctrlor list
      * returns: 如果达到末尾,则返回false
      */
    if(list != nullptr)
    {
        this->current_img_list = list;
        return true;
    }else
        return false;
}

QString imager_ctrlor::next_pic()
{
    qDebug() << index << " " << current_img_list->length();
    if(this->index<this->current_img_list->length()-1){
        this->index++;
    }else{
        // 下一组
        if(this->set_img_list(pw->get_img_grp(NEXT)))
            index = 0;
        else
            return QString("tail");
    }
    return (*this->current_img_list)[this->index];
}

QString imager_ctrlor::pre_pic()
{
    if(this->index > 0){

        this->index--;
    }else{
        // 上一组
        if(this->set_img_list(pw->get_img_grp(PREVIOUS)))
            this->index = this->current_img_list->length()-1;
        else
            return QString("head");
    }
    return (*this->current_img_list)[this->index];
}
