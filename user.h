#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();


private slots:


    void on_pushButton_load_clicked();

    void on_pushButton_AddReview_clicked();


private:
    Ui::user *ui;
};

#endif // USER_H
