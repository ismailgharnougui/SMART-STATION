#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_client->setModel(Etmp.afficher());
ui->CIN->setValidator(new QIntValidator(0,99999999,this));
ui->NUMTEL->setValidator(new QIntValidator(0,99999999,this));
ui->NBRJOURS->setValidator(new QIntValidator(0,31,this));

}


MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButtonAjouter_clicked()
{
    QString  id=ui->ID->text();
    int cin=ui->CIN->text().toInt();
    QString nom=ui->NOM->text();
    QString prenom=ui->PRENOM->text();
    int numtel=ui->NUMTEL->text().toInt();
    QString adresse=ui->ADRESSE->text();
    QString dateres=ui->DATERES->text();
    int nbrjours=ui->NBRJOURS->text().toInt();


    Client C(id,cin,nom,prenom,numtel,adresse,dateres,nbrjours);
bool test=C.ajouter();
if (test)
        { //Actualiser
     ui->tab_client->setModel(Etmp.afficher());
        QMessageBox:: information(nullptr, QObject::tr("OK"),
                                           QObject::tr("Ajout effectué\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);
        }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_id_supp_clicked()
{
    Client c;c.setid(ui->id2->text());
        bool test=Etmp.supprimer(c.get_id());
        QMessageBox msgBox;
        if (test)
                {
            //actualiser
             ui->tab_client->setModel(Etmp.afficher());
                QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                   QObject::tr("Suppression effectué\n"
                                                               "click cancel to exit."),QMessageBox::Cancel);
                }
            else
                QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                      QObject::tr("Suppression non effectué.\n"
                                                  "click Cancel to exit."),QMessageBox::Cancel);

}






