#ifndef JPLHCONNECTIONBASE_H
#define JPLHCONNECTIONBASE_H

#include "jconnectionbase.h"

class JPlhConnectionBase : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JPlhConnectionBase(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray &);
	virtual void afterPlh(const QByteArray&);
};

#endif // JPLHCONNECTIONBASE_H
