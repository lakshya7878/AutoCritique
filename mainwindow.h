#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static QString login_id;
public:
    QSqlDatabase mydb;
    bool openConnection(){
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/Users/lakshyasharma/Desktop/sqlitelearn.sqlite");
        if(!mydb.open()) return false;
        return true;
    }
    void closeConnection(){
        mydb.close();
    }
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_clicked();
    void on_SignUp_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
