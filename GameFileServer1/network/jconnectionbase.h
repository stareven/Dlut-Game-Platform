#ifndef JCONNECTIONBASE_H
#define JCONNECTIONBASE_H

#include <QObject>

#include "jglobal.h"

class QTcpSocket;

class JConnectionBase : public QObject
{
Q_OBJECT
public:
    explicit JConnectionBase(QTcpSocket* socket,QObject *parent = 0);
    virtual ~JConnectionBase(){}
private:
    QTcpSocket* m_socket;
private slots:
    void on_socket_readyRead();
protected slots:
    virtual void on_socket_disconnected();
protected:
    virtual void dataProcess(const QByteArray&);
    void sendData(const QByteArray&);
    void closeConnect();
private:
    JID m_userid;
public:
    JID getUserId()const;
protected:
    void setUserId(JID userid);
};

#endif // JCONNECTIONBASE_H
