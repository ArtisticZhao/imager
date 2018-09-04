#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMovie>
#include <QLabel>
#include "imager_ctrlor.h"
#include "path_walker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_imager_ctrlor(imager_ctrlor*);
    void set_path_walker(path_walker*);

private slots:

    void on_right_clicked();

    void on_left_clicked();

    void on_next_album_clicked();

    void on_pre_album_clicked();

    void on_open_path_triggered();

    void on_tags_edit_returnPressed();

    void on_open_database_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap image;
    QMovie *gif=nullptr;
    imager_ctrlor *img_ctrlor;
    path_walker *pw;

    void show_image(QString path);
    void updata_statusbar();
    void updata_all_info();
    void todo_after_path_walk();
};

#endif // MAINWINDOW_H
