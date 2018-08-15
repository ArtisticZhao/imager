#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmapCache>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置每次只加入一张图片在缓冲区，多次load在内存中只有一个图片
    QPixmapCache::setCacheLimit(1);
    ui->image_shower->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_image_path_returnPressed()
{
    QString filename = ui->image_path->text();
    show_image(filename);
}

void MainWindow::on_open_btn_clicked()
{
    // 在此处打开文件浏览窗口
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty())
    {
        ui->image_path->setText(filename);
        show_image(filename);
    }
}

void MainWindow::show_image(QString path)
{
    //显示图片
    image.load(path);
    int w = ui->image_shower->width();
    int h = ui->image_shower->height();
    ui->image_shower->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
}
