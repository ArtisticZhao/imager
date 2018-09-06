#include "choose_tags_dialog.h"
#include "ui_choose_tags_dialog.h"
#include <QDebug>
choose_tags_dialog::choose_tags_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choose_tags_dialog)
{
    ui->setupUi(this);


}

choose_tags_dialog::~choose_tags_dialog()
{
    delete ui;
}

void choose_tags_dialog::set_gen_checkbox(const QList<QString>& tags)
{
    this->ui->listWidget->addItems(tags);
    QListWidgetItem *item = nullptr;
    for(int i=0;i<tags.length();++i){
        item = this->ui->listWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
}

void choose_tags_dialog::set_path_walker(path_walker *pw)
{
    this->pw = pw;
}

void choose_tags_dialog::on_buttonBox_accepted()
{
    QString selected_tags;
    bool is_head = true;
    for(int i=0;i<this->ui->listWidget->count();++i){
        if(this->ui->listWidget->item(i)->checkState()){
            if(is_head){
                selected_tags += this->ui->listWidget->item(i)->text();
                is_head = false;
            }else{
                selected_tags += ',';
                selected_tags += this->ui->listWidget->item(i)->text();
            }
        }
    }
    qDebug()<<selected_tags;
    emit this->send_selected_tags(selected_tags);
}
