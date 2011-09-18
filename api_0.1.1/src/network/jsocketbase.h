#ifndef JSOCKETBASE_H
#define JSOCKETBASE_H

#include <QObject>
#include <QAbstractSocket>
#include <QHash>

class QTcpSocket;

class JSocketBase : public QObject{
    Q_OBJECT
public:
    explicit JSocketBase(QTcpSocket* const socket,QObject* parent=0);
    JCode registerProcessor(JID type,JNetworkDataProcessorBase*);
    JCode sendData(const QByteArray&);
    QAbstractSocket::SocketState socketState () const;
signals:
    void disconnected();
    void error ( QAbstractSocket::SocketError socketError );
protected:
    virtual JCode init()=0;
    QTcpSocket* const m_socket;
private slots:
    void on_socket_readyRead();
private:
    QHash<JID,JNetworkDataProcessorBase*> m_processors;
};

#endif // JSOCKETBASE_H
