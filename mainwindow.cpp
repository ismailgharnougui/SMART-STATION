
#include "smtp.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>




#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->ID_REPARATION->setValidator(new QIntValidator(0,999999999,this));
    ui->tab_reparation->setModel(R.afficher());
    ui->ID_REPARATION->setValidator(new QIntValidator(0,999999999,this));

        ui->le_debut->setMaxLength(10);
        ui->DATE_DISPO->setMaxLength(10);
        ui->l_facture->setMaxLength(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    QString id_reparation=ui->ID_REPARATION->text();
    QString piece=ui->le_piece->text();
    QString panne=ui->le_panne->currentText();
    QString date_dispo=ui->DATE_DISPO->text();
    QString date_debut=ui->le_debut->text();
    QString facture=ui->l_facture->text();
 Reparations R(id_reparation,piece,panne,date_dispo,date_debut,facture);
 bool test=R.ajouter();
 if (test)
         { //Actualiser
      ui->tab_reparation->setModel(R.afficher());
         QMessageBox:: information(nullptr, QObject::tr("OK"),
                                            QObject::tr("Ajout effectué\n"
                                                        "click cancel to exit."),QMessageBox::Cancel);
         }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                               QObject::tr("Ajout non effectué.\n"
                                           "click Cancel to exit."),QMessageBox::Cancel);
 }



void MainWindow::on_pb_supprimer_clicked()
{
 Reparations R;
R.setid_reparation(ui->le_id_supp->text().toInt());
bool test=R.supprimer(R.getid_reparation());
QMessageBox msgBox;
if (test)
{
    msgBox.setText("Suppression avec succes.");
    ui->tab_reparation->setModel(R.afficher());
}else
 msgBox.setText("Echec de suppresion.");

msgBox.exec();

}
void MainWindow::on_date_dispo_modifier_clicked()
{

    QString id_reparation=ui->id_reparation->text();
    QString piece=ui->le_piece->text();
    QString panne=ui->le_panne->currentText();
    QString date_dispo=ui->date_dispo->text();
    QString date_debut=ui->le_debut->text();
    QString facture=ui->l_facture->text();
    Reparations R(id_reparation,piece,panne,date_debut,date_dispo,facture);

    if (date_dispo.isEmpty())
                 {
                     QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("remplir la date dispo svp."),QMessageBox::Cancel);
                 }
             else
             {
         bool test=R.modifier(id_reparation);

         if (test)
                 { //Actualiser
              ui->tab_reparation->setModel(R.afficher());
                 QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                    QObject::tr("Modifier la reparation effectué©\n"
                                                                "click cancel to exit."),QMessageBox::Cancel);
                 }
             else
                 QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                       QObject::tr("Ajout non effectué.\n"

                                           "click Cancel to exit."),QMessageBox::Cancel);}
}
void MainWindow::on_rechercher_button_clicked()
{
    QString rech =ui->id_reparation->text();
        ui->tab_reparation->setModel(R.rechercher(rech));
}



void MainWindow::on_radioButton_croissant_clicked()
{
     ui->tab_reparation->setModel(R.tri());
}

void MainWindow::on_radioButton_dcroissant_clicked()
{
     ui->tab_reparation->setModel(R.trid());
}

// stat sur les destinations
void MainWindow::on_statsmed_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from REPARATION where PANNE='panne de batterie' ");
     int number1=model->rowCount();
     model->setQuery("select * from REPARATION where PANNE='fuite du joint' ");
     int number2=model->rowCount();
     model->setQuery("select * from REPARATION where PANNE='refroidissement' ");
     int number3=model->rowCount(); // calculer le nombre de panne pour refroidissement
    model->setQuery("select * from REPARATION where PANNE='roues' ");
          int number4=model->rowCount();
          model->setQuery("select * from REPARATION where PANNE='huile moteur' ");
          int number5=model->rowCount();
     model->setQuery("select * from REPARATION where DESTINATION='autre' ");
     int number6=model->rowCount();
     int total=number1+number2+number3+number4+number5+number6;
     QString a = QString("panne de batterie  "+QString::number((number1*100)/total,'f',2)+"%" );
     QString b = QString("fuite du joint "+QString::number((number2*100)/total,'f',2)+"%" );
     QString c = QString("refroidissement"+QString::number((number3*100)/total,'f',2)+"%" );
     QString d = QString("roues" +QString::number((number4*100)/total,'f',2)+"%" );

      QString e = QString("huile moteur" +QString::number((number5*100)/total,'f',2)+"%" );

     QString f = QString("autre "+QString::number((number6*100)/total,'f',2)+"%" );


     QPieSeries *series = new QPieSeries();
     series->append(a,number1);
     series->append(b,number2);
     series->append(c,number3);
     series->append(d,number4);
     series->append(e,number5);
     series->append(f,number6);
     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
     }
     if(number3!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice2 = series->slices().at(2);
              //slice1->setExploded();
              slice2->setLabelVisible();
     }
     if(number4!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice3 = series->slices().at(3);
              //slice1->setExploded();
              slice3->setLabelVisible();
     }
     if(number5!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice4 = series->slices().at(4);
              //slice1->setExploded();
              slice4->setLabelVisible();
     }
     if(number6!=0)
     {
              // Add labels to rest of slices
              QPieSlice *slice5 = series->slices().at(5);
              //slice1->setExploded();
              slice5->setLabelVisible();
     }
             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("Pourcentage Par Type DE PANNE :Nombre Des PANNE "+ QString::number(total));
             chart->legend()->hide();
             // Used to display the chart
             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(1000,500);
             chartView->show();

}


void MainWindow::on_pushButton_browse_email_clicked()
{ files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->lineEdit_atchmnt_email->setText( fileListString );

}




void MainWindow::on_pushButton_send_email_clicked()
{
    //    QSslConfiguration sslCfg = QSslConfiguration::defaultConfiguration();
        //    QList<QSslCertificate> ca_list = sslCfg.caCertificates();
        //    QList<QSslCertificate> ca_new = QSslCertificate::fromData("CaCertificates");
        //    ca_list += ca_new;

        //    sslCfg.setCaCertificates(ca_list);

        //    sslCfg.setProtocol( QSsl::TlsV1SslV3 );

        //    QSslConfiguration::setDefaultConfiguration(sslCfg);

            qDebug() <<  "Loaded SSL Library version: " << QSslSocket::sslLibraryVersionString();

            // ui->lineEdit_to_email->setText("email_ili_bch_tab3athlou@gmail.com");
            // ui->lineEdit_from_email->setText("email_ili_bch_tab3ith_minou@gmail.com");
            // ui->lineEdit_psswrd_email->setText("mdp mta3 l email ili bch tab3th minou");

            // ui->lineEdit_subject_email->setText("test subject");
            // ui->textEdit_email->setText("test text");

            QString from = ui->lineEdit_from_email->text();
            QString to = ui->lineEdit_to_email->text();
            QString subject = ui->lineEdit_subject_email->text();
            QString password = ui->lineEdit_psswrd_email->text();
            QString email_text = ui->textEdit_email->toPlainText();

            Smtp* smtp = new Smtp(from, password);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            if( !files.isEmpty() )
                smtp->sendMail(from, to, subject, email_text, files);
            else
                smtp->sendMail(from, to, subject, email_text);

}
