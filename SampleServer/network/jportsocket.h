#ifndef JPORTSOCKET_H
#define JPORTSOCKET_H

#include "jsocketbase.h"
#include "eportsrv.h"

class JPortSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JPortSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
    void rqsServerPort(EServerType);
protected:
    void dataProcess(const QByteArray&);
signals:
    void rcvPassLoginHash(bool);
    void rcvServerPort(quint16);
};

#endif // JPORTSOCKET_H
