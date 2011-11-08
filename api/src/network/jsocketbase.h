#ifndef JSOCKETBASE_H
#define JSOCKETBASE_H

#include <QObject>
#include <QAbstractSocket>
#include <QHash>

#include "../global/jglobal.h"

class QTcpSocket;

class JNetworkDataProcessorBase;
class JSession;

class JSocketBase : public QObject{
    Q_OBJECT
public:
    explicit JSocketBase(QTcpSocket* const socket,QObject* parent=0);
	JCode registerProcessor(JNetworkDataProcessorBase*);
	JCode sendData(JType type,const QByteArray&);
    QAbstractSocket::SocketState socketState () const;
public:
	JSession* getSession()const;
private:
	JSession* m_session;
signals:
    void disconnected();
	void error ( JCode errorCode );
protected:
    QTcpSocket* const m_socket;
private slots:
    void on_socket_readyRead();
	void on_socket_error(QAbstractSocket::SocketError);
	void on_socket_connected();
private:
	QHash<JType,JNetworkDataProcessorBase*> m_processors;
	JType m_type;
    qint32 m_size;
    QByteArray m_data;
};

#endif // JSOCKETBASE_H
