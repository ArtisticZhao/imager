#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "path_walker.h"
#include "imager_ctrlor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    path_walker pw;
//    pw.walk_path("Z:/全屏看图");
//    qDebug()<<"done!";
//    qDebug()<<"----------------------";
    imager_ctrlor ic(&pw);
    w.set_imager_ctrlor(&ic);
    w.set_path_walker(&pw);
    return a.exec();
}
