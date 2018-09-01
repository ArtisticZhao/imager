#ifndef IMAGER_CTRLOR_H
#define IMAGER_CTRLOR_H

/* 本类用于连接显示与文件系统,为将来扩展数据库使用
 * path walker 类能够产生图片路径列表
 * main window 中则实现了图像的显示功能
 * 该类应该能够接收来自mainwindow中的信号,达到上下翻页的目的.
 * */

#include <QList>
#include "path_walker.h"

#define PREVIOUS 0
#define NEXT 1

class imager_ctrlor
{
private:
    path_walker *pw;
    const QList<QString> *album_paths;
    const QList<QString> *current_img_list;
    int album_index=0;
    int img_index=0;
    int current_len=0;
    int album_len=0;
    QString album_name;

    bool set_img_list(int direct);

public:
    imager_ctrlor(path_walker *pw);
    void init_imager_ctrlor();
    QString get_album_name();
    // entry
    bool pre_album();
    bool next_album();
    QString next_pic();
    QString pre_pic();
};

#endif // IMAGER_CTRLOR_H
