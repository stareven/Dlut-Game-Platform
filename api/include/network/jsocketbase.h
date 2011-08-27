#ifndef JSOCKETBASE_H
#define JSOCKETBASE_H

#include <QObject>
#include <QAbstractSocket>

#include "global/jglobal.h"
#include "global/magicnumber.h"
#include "clientapi_global.h"

class QTcpSocket;
class QHostAddress;

class CLIENTAPISHARED_EXPORT JSocketBase : public QObject
{
    Q_OBJECT
public:
    explicit JSocketBase(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,
                       quint16 port);
    bool isConnected()const;
	QAbstractSocket::SocketState socketState () const;
private:
    QTcpSocket *m_socket;
	qint32 m_size;
	QByteArray m_data;

signals:
    void SocketCode(ENet netcode);
	void SocketError(QString);
protected slots:
    void on_socket_connected();
    void on_socket_disconnected();
    void on_socket_readyRead();
    void on_socket_error ( QAbstractSocket::SocketError socketError );
private:
	virtual MagicNumber::JMagicNumber getMagicNumber()const=0;

protected:
    virtual void dataProcess(const QByteArray&)=0;
    void sendData(const QByteArray&);
	void closeConnect();
};

#endif // JSOCKETBASE_H
