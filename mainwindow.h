#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_image_path_returnPressed();

    void on_open_btn_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap image;
    void show_image(QString path);
};

#endif // MAINWINDOW_H
