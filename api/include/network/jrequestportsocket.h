#ifndef JREQUESTPORTSOCKET_H
#define JREQUESTPORTSOCKET_H

#include "jsocketbase.h"
#include "global/eportsrv.h"

class JRequestPortSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JRequestPortSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
    void rqsServerPort(EServerType);
protected:
    void dataProcess(const QByteArray&);
signals:
    void rcvPassLoginHash(bool);
    void rcvServerPort(quint16);
};

#endif // JREQUESTPORTSOCKET_H
