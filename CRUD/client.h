#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{public:
    Client();
    Client(QString,int,QString,QString,int,QString,QString,int);
    QString  get_id();
    int  get_cin();
    QString get_nom();
    QString get_prenom();
    int get_numtel();
    QString get_adresse();
    QString get_dateres();
    int  get_nbrjours();

    void  setid(QString);
    void  setcin(int);
    void  setnom(QString);
    void  setprenom(QString);
    void  setnumtel( int);
    void  setadresse(QString);
    void  setdateres(QString);
    void  setnbrjours(int);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);

private:
    QString id,nom,prenom,adresse,dateres;
    int cin,numtel,nbrjours;
};

#endif // CLIENT_H
