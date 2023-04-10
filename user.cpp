#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"

user::user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{

    ui->setupUi(this);
    ui->Welcome->setAlignment(Qt::AlignCenter);
    ui->label_addReview->setAlignment(Qt::AlignCenter);
    ui->ReviewStatus->setAlignment(Qt::AlignCenter);
    ui->comboBox_carlist->addItem("Volkswagen");
    ui->comboBox_carlist->addItem("Ferrari");
    ui->comboBox_carlist->addItem("BMW");
    ui->comboBox_carlist->addItem("Jaguar");
    ui->comboBox_carlist->addItem("Hellcat");

    ui->comboBox_sortby->addItem("Price");
    ui->comboBox_sortby->addItem("Rating");
    ui->comboBox_sortby->addItem("Launch year");
    MainWindow conn;
    if(conn.openConnection()){
        ui->status->setText("Connected");
    }
    else{
        ui->status->setText("Failed to connect to DataBase");
    }
    ui->Welcome->setText("Welcome " + conn.login_id);
    conn.closeConnection();
}

user::~user()
{
    delete ui;
}


void user::on_pushButton_load_clicked()
{
    MainWindow conn;
    conn.openConnection();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry(conn.mydb);
    QString curr = ui->comboBox_sortby->currentText();
    if(curr=="Price"){
        qry.prepare("SELECT CarName, Price, Rating, Keywords, LaunchYear FROM CarDetails ORDER BY Price");
    }
    else if(curr=="Rating"){
        qry.prepare("SELECT CarName, Price, Rating, Keywords, LaunchYear FROM CarDetails ORDER BY Rating");
    }
    else if(curr=="Launch year"){
        qry.prepare("SELECT CarName, Price, Rating, Keywords, LaunchYear FROM CarDetails ORDER BY Launchyear");
    }
    else{
        ui->ReviewStatus->setText("Please Select a Category to sorty by");
        return;
    }

    if(!qry.exec())
        qDebug()<<qry.lastError().text();
    else
        qDebug()<<"Loaded data in Table View";
    model->setQuery(qry);
    ui->CarDetailsTableView->setModel(model);
    ui->CarDetailsTableView->show();
    conn.closeConnection();
}


void user::on_pushButton_AddReview_clicked()
{
    MainWindow conn;
    conn.openConnection();
    QString keyfeat,Name;
    quint64 rate;
    keyfeat = ui->lineEdit_KeyFeaturees->text();
    Name = ui->comboBox_carlist->currentText();
    rate = ui->lineEdit_ratingten->text().toInt();
    if(rate>10 || rate<0){
        ui->ReviewStatus->setText("Enter a valid rating value");
        return;
    }
    qDebug()<<rate;
    QSqlQuery qry;
    qry.prepare(" UPDATE CarDetails SET Keywords = Keywords || ',' ||  '"+keyfeat+"' , Ratingsm = Ratingsm + :rate,Ratingcnt = Ratingcnt+1 WHERE CarName = '"+Name+"' ");
    qry.bindValue(":rate",rate);
    if(!qry.exec() )
    {
        qDebug() << qry.lastError().text();
    }
    if(qry.numRowsAffected()>0)
    {
         ui->ReviewStatus->setText("Review Added!!!");
    }
    else
    {
     qDebug() << "Unable to add Review";
    }
    qry.prepare("UPDATE CarDetails SET Rating = CAST(Ratingsm/Ratingcnt AS FLOAT) WHERE CarName = '"+Name+"'");
    qry.exec();
    conn.closeConnection();
}




