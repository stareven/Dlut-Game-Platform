#ifndef JSERVERTYPE_H
#define JSERVERTYPE_H

#include <QObject>

#include "global/eportsrv.h"
#include "network/jserverbase.h"

class JServerType : public JServerBase
{
Q_OBJECT
public:
    explicit JServerType(EServerType,QObject *parent = 0);
    EServerType serverType()const;

protected:
	const EServerType m_servertype;
protected:
	JConnectionBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JSERVERTYPE_H
