#ifndef JGAMEINFOCONNECTION_H
#define JGAMEINFOCONNECTION_H

#include "jplhconnectionbase.h"

class JGameInfoConnection : public JPlhConnectionBase
{
    Q_OBJECT
public:
    explicit JGameInfoConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void afterPlh(const QByteArray&);
};

#endif // JGAMEINFOCONNECTION_H
