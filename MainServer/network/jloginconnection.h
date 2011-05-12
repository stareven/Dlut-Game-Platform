#ifndef JLOGINCONNECTION_H
#define JLOGINCONNECTION_H

#include "jconnectionbase.h"

class JLoginConnection : public JConnectionBase
{
Q_OBJECT
public:
    explicit JLoginConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
    virtual void dataProcess(const QByteArray&);
};

#endif // JLOGINCONNECTION_H
