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
    imager_ctrlor ic(&pw);
    w.set_imager_ctrlor(&ic);
    w.set_path_walker(&pw);
    pw.test_get_by_tags();
    return a.exec();
}
