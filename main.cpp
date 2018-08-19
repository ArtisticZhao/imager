#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "path_walker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    path_walker pw;
//    pw.print_files("E:\\HIT");
    pw.walk_path("C:\\Users\\Artistic Zhao\\Pictures\\Camera Roll");
    qDebug()<<"----------------------";
    pw.show_paths();
    return a.exec();
}
