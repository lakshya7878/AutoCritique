#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include<iostream>

QString MainWindow::login_id;
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);

    if(!openConnection()){
        ui->label->setText("Failed to open DB");
    }
    else{
        ui->label->setText("Connected");
    }
    closeConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_login_clicked()
{
    if(openConnection()){
        qDebug()<<"Failed to open the database";
    }
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();
    QSqlQuery qry;
    QString who = "SELECT * FROM employee WHERE name = '" + username + "' AND password = '" + password + "'";
    qDebug()<<who;
    qry.prepare(who);
    if(!qry.exec() )
    {
        qDebug() << qry.lastError().text();
    }
    else{
        int cnt = 0;
        while(qry.next()){
            cnt++;
        }
        if(cnt==1){
            ui->label->setText("Correct");
            login_id = username;
            hide();
            user *NewLogin = new user();
            NewLogin->show();
        }
        else if (cnt>1){
            ui->label->setText("Duplicate username and passwords");
        }
        else{
            ui->label->setText("Incorrect Username or password");
        }
    }
    closeConnection();
}

void MainWindow::on_SignUp_clicked()
{
    if(openConnection()){
        qDebug()<<"Failed to open the database";
    }
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();
    if(!mydb.open()){
        qDebug()<<"Failed to open the database";
    }
    QSqlQuery qry;
    qry.prepare("SELECT COUNT(name) FROM employee WHERE name = '"+username+"'");
    qry.exec();
    while(qry.next()){
        quint64 val = qry.value(0).toInt();
        if(val==1){
            ui->label->setText("Username already taken.");
        }
        else{
            qry.prepare("INSERT INTO employee VALUES('"+username+"','"+password+"'");
            qry.exec();
            ui->label->setText("You've been signed up!!!");
        }
    }
    closeConnection();
}











