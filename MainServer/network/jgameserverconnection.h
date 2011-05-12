#ifndef JGAMESERVERCONNECTION_H
#define JGAMESERVERCONNECTION_H

#include "jconnectionbase.h"

class JGameServerConnection : public JConnectionBase
{
    Q_OBJECT
public:
    explicit JGameServerConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
    virtual void dataProcess(const QByteArray&);
private:
    bool m_passLoginHash;
};

#endif // JGAMESERVERCONNECTION_H
