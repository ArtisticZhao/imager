#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include "imager_ctrlor.h"
#include "path_walker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set_imager_ctrlor(imager_ctrlor*);
    void set_path_walker(path_walker*);

private slots:
    void on_image_path_returnPressed();

    void on_open_btn_clicked();

    void on_right_clicked();

    void on_left_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap image;
    imager_ctrlor *ic;
    path_walker *pw;
    void show_image(QString path);
};

#endif // MAINWINDOW_H
