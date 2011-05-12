#ifndef JGSINFOSOCKET_H
#define JGSINFOSOCKET_H

#include "jsocketbase.h"
#include "sgame.h"

class JGsInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JGsInfoSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
    void sendGsInfo(const SGameInfo&);
protected:
    void dataProcess(const QByteArray&);
signals:
    void rcvPassLoginHash(bool);
    void rcvGsInfo(JID);
};

#endif // JGSINFOSOCKET_H
