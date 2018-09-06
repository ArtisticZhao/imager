#ifndef CHOOSE_TAGS_DIALOG_H
#define CHOOSE_TAGS_DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include "path_walker.h"

namespace Ui {
class choose_tags_dialog;
}

class choose_tags_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit choose_tags_dialog(QWidget *parent = nullptr);
    ~choose_tags_dialog();
    void set_gen_checkbox(const QList<QString>& tags);
    void set_path_walker(path_walker *pw);
private slots:
    void on_buttonBox_accepted();
signals:
    void send_selected_tags(const QString& tags);

private:
    QList<QString> all_tags;
    QList<QCheckBox*> tag_choose_list;
    path_walker *pw;
    Ui::choose_tags_dialog *ui;
};

#endif // CHOOSE_TAGS_DIALOG_H
