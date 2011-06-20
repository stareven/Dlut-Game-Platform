#ifndef JPORTCONNECTION_H
#define JPORTCONNECTION_H

#include "network/jconnectionbase.h"
#include "service/jportmanager.h"

class JPortConnection : public JConnectionBase
{
    Q_OBJECT
public:
    explicit JPortConnection(JPortManager::EPortServer,QTcpSocket* socket,QObject *parent = 0);

private:
    JPortManager m_srv;
protected:
    virtual void dataProcess(const QByteArray&);

private:
    bool m_passLoginHash;
};

#endif // JPORTCONNECTION_H
