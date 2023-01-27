#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("gestionclients");//inserer le nom de la source de données ODBC
db.setUserName("iheb001");//inserer nom de l'utilisateur
db.setPassword("iheb");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

    return  test;
}
void Connection::closeConnection(){db.close();}
