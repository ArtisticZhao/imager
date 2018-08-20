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
    pw.walk_path("C:\\Users\\Artistic Zhao\\Pictures\\Camera Roll");
    qDebug()<<"all_paths------------------";
    pw.show_paths();
    qDebug()<<"----------------------";
    imager_ctrlor ic(&pw);
    w.set_imager_ctrlor(&ic);

    return a.exec();
}
