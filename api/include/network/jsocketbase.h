#ifndef JSOCKETBASE_H
#define JSOCKETBASE_H

#include <QObject>
#include <QAbstractSocket>

#include "global/jglobal.h"

class QTcpSocket;
class QHostAddress;

class JSocketBase : public QObject
{
    Q_OBJECT
public:
    explicit JSocketBase(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,
                       quint16 port);
    bool isConnected()const;
private:
    QTcpSocket *m_socket;
	int m_size;
	QByteArray m_data;

signals:
    void SocketCode(JCode code);

protected slots:
    void on_socket_connected();
    void on_socket_disconnected();
    void on_socket_readyRead();
    void on_socket_error ( QAbstractSocket::SocketError socketError );

protected:
    virtual void dataProcess(const QByteArray&)=0;
    void sendData(const QByteArray&);
    void closeConnect();
	QAbstractSocket::SocketState socketState()const;
};

#endif // JSOCKETBASE_H