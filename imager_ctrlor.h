#ifndef IMAGER_CTRLOR_H
#define IMAGER_CTRLOR_H

/* 本类用于连接显示与文件系统,为将来扩展数据库使用
 * path walker 类能够产生图片路径列表
 * main window 中则实现了图像的显示功能
 * 该类应该能够接收来自mainwindow中的信号,达到上下翻页的目的.
 * */

#include <QList>
#include "path_walker.h"

class imager_ctrlor
{
public:
    imager_ctrlor(path_walker *pw);
    bool set_img_list(QList<QString> *list);
    QString next_pic();
    QString pre_pic();
private:
    path_walker *pw;
    QList<QString> *current_img_list;
    int index=0;
};

#endif // IMAGER_CTRLOR_H
