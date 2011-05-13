#ifndef JGAMESERVERCONNECTION_H
#define JGAMESERVERCONNECTION_H

#include "jconnectionbase.h"

class JGameServerConnection : public JConnectionBase
{
    Q_OBJECT
public:
    explicit JGameServerConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
    void dataProcess(const QByteArray&);
    void on_socket_disconnected();
private:
    bool m_passLoginHash;
    JID m_gameid;
};

#endif // JGAMESERVERCONNECTION_H
