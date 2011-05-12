#ifndef JLOGINSOCKET_H
#define JLOGINSOCKET_H

#include <QObject>

#include "jglobal.h"

class QTcpSocket;
class QHostAddress;

class JLoginSocket : public QObject
{
Q_OBJECT
public:
    explicit JLoginSocket(QObject *parent = 0);

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
#endif // JLOGINSOCKET_H
