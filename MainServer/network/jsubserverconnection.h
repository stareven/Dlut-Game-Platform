#ifndef JSUBSERVERCONNECTION_H
#define JSUBSERVERCONNECTION_H

#include "jconnectionbase.h"

class JSubServerConnection : public JConnectionBase
{
    Q_OBJECT
public:
    explicit JSubServerConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
    void dataProcess(const QByteArray&);
    void on_socket_disconnected();
private:
    bool m_passLoginHash;
    JID m_gameid;
};

#endif // JSUBSERVERCONNECTION_H
