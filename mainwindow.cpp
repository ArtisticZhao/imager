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
    this->img_ctrlor = ic;
}

void MainWindow::set_path_walker(path_walker *pw)
{
    this->pw=pw;
}

void MainWindow::show_image(QString path)
{
    /**
     * 如果输入的后缀名为.gif则使用QMovie播放
     **/
    // debug
    qDebug()<<path;
    // 显示图片
    if(QString::compare(path, QString("tail")) && QString::compare(path, QString("head"))){
        ui->right->setDisabled(false);
        ui->left->setDisabled(false);
        int w = ui->image_shower->width();
        int h = ui->image_shower->height();
        if(!QString::compare(path.mid(path.lastIndexOf('.')+1), QString("gif"))||
                !QString::compare(path.mid(path.lastIndexOf('.')+1), QString("GIF"))){
            // play gif
            if(this->gif != nullptr){
                delete this->gif;
            }
            // get size
            image.load(path);

            this->gif = new QMovie(path);
            this->gif->stop();
            // 自适应窗口
            this->gif->setScaledSize(this->image.size().scaled(w,h,Qt::KeepAspectRatio));
            this->ui->image_shower->setMovie(this->gif);
            this->gif->start();
        }else{
            image.load(path);
            ui->image_shower->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
        }
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
    show_image(this->img_ctrlor->next_pic());
    this->setWindowTitle(this->img_ctrlor->get_album_name());
}

void MainWindow::on_left_clicked()
{
    show_image(this->img_ctrlor->pre_pic());
    this->setWindowTitle(this->img_ctrlor->get_album_name());
}

void MainWindow::on_next_album_clicked()
{
    this->ui->pre_album->setEnabled(true);
    if(!this->img_ctrlor->next_album()){
        this->ui->next_album->setEnabled(false);
    }
    show_image(this->img_ctrlor->next_pic());
    this->setWindowTitle(this->img_ctrlor->get_album_name());
}

void MainWindow::on_pre_album_clicked()
{
    this->ui->next_album->setEnabled(true);
    if(!this->img_ctrlor->pre_album()){
        this->ui->pre_album->setEnabled(false);
    }
    show_image(this->img_ctrlor->next_pic());
    this->setWindowTitle(this->img_ctrlor->get_album_name());
}


void MainWindow::on_open_path_triggered()
{
    // 在此处打开文件浏览窗口
    QString dirname = QFileDialog::getExistingDirectory(this);
    if(!dirname.isEmpty())
    {
        // TODO: has some problems!
        qDebug()<<"root: "<<dirname;
        pw->walk_path(dirname, true);
        // DEBUG
        qDebug()<<"done walk!";
        pw->show_paths();
        qDebug()<<"---------------------";
        this->img_ctrlor->init_imager_ctrlor();
        // 解除按钮限制
        this->ui->left->setEnabled(true);
        this->ui->right->setEnabled(true);
        this->ui->pre_album->setEnabled(true);
        this->ui->next_album->setEnabled(true);
        // 载入第一张
        this->show_image(this->img_ctrlor->next_pic());
        this->setWindowTitle(this->img_ctrlor->get_album_name());
    }
}
