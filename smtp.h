#ifndef SMTP_H
#define SMTP_H

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp( const QString &user, const QString &pass,
          const QString &host="smtp.gmail.com", int port=465, int timeout=30000 );
    ~Smtp();

    void sendMail( const QString &from, const QString &to,
                   const QString &subject, const QString &body,
                   QStringList files = QStringList());

signals:
    void status( const QString &);

private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

private:
    QTextStream *t;
    QSslSocket *socket;
    QString message;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int timeout;
    int port;
    int state;
    enum states{Tls,HandShake,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};

};

#endif // SMTP_H
