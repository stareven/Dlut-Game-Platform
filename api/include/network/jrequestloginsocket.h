#ifndef JREQUESTLOGINSOCKET_H
#define JREQUESTLOGINSOCKET_H

#include <QObject>

#include "global/jglobal.h"

class QTcpSocket;
class QHostAddress;

class JRequestLoginSocket : public QObject
{
Q_OBJECT
public:
    explicit JRequestLoginSocket(QObject *parent = 0);

    void login(const QString& loginname,const QString& passwd,const JID& role);
    void connectToHost(const QHostAddress& address,
		       quint16 port);
private:
    QTcpSocket *m_socket;

signals:
    void loginCode(const JCode& code);

protected slots:
    void on_socket_connected();
    void on_socket_disconnected();
    void on_socket_readyRead();
private:
    JID m_userid;
    QByteArray m_crypro;
public:
    JID getUserId()const;
    const QByteArray& getCrypro()const;
};
#endif // JREQUESTLOGINSOCKET_H
