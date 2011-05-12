#ifndef JGAMEINFOCONNECTION_H
#define JGAMEINFOCONNECTION_H

#include "jconnectionbase.h"

class JGameInfoConnection : public JConnectionBase
{
    Q_OBJECT
public:
    explicit JGameInfoConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
    virtual void dataProcess(const QByteArray&);
private:
    bool m_passLoginHash;
};

#endif // JGAMEINFOCONNECTION_H
