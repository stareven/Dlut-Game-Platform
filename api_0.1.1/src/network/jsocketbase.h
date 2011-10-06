#ifndef JSOCKETBASE_H
#define JSOCKETBASE_H

#include <QObject>
#include <QAbstractSocket>
#include <QHash>

#include "../global/jglobal.h"

class QTcpSocket;

class JNetworkDataProcessorBase;

class JSocketBase : public QObject{
    Q_OBJECT
public:
    explicit JSocketBase(QTcpSocket* const socket,QObject* parent=0);
	JCode registerProcessor(JType type,JNetworkDataProcessorBase*);
	JCode sendData(JType type,const QByteArray&);
    QAbstractSocket::SocketState socketState () const;
signals:
    void disconnected();
    void error ( QAbstractSocket::SocketError socketError );
protected:
    QTcpSocket* const m_socket;
private slots:
    void on_socket_readyRead();
private:
	QHash<JType,JNetworkDataProcessorBase*> m_processors;
	JType m_type;
    qint32 m_size;
    QByteArray m_data;
};

#endif // JSOCKETBASE_H
