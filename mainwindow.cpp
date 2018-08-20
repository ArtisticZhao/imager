#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmapCache>
#include <QDebug>


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

void MainWindow::set_imager_ctrlor(imager_ctrlor *ic)
{
    this->ic = ic;
}

void MainWindow::set_path_walker(path_walker *pw)
{
    this->pw=pw;
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
    // debug
    qDebug()<<path;
    // 显示图片
    if(QString::compare(path, QString("tail")) && QString::compare(path, QString("head"))){
        ui->right->setDisabled(false);
        ui->left->setDisabled(false);
        image.load(path);
        int w = ui->image_shower->width();
        int h = ui->image_shower->height();
        ui->image_shower->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
    }else if(path == QString("tail")){
        ui->image_shower->setText("已经是最后一张了!");
        ui->right->setDisabled(true);
    }else{
        ui->image_shower->setText("已经是第一张了!");
        ui->left->setDisabled(true);
    }

}

void MainWindow::on_right_clicked()
{
    show_image(this->ic->next_pic());
}

void MainWindow::on_left_clicked()
{
    show_image(this->ic->pre_pic());
}
