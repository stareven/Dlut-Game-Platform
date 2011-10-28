#ifndef JPLHCONNECTIONBASE_H
#define JPLHCONNECTIONBASE_H

#include "network/jconnectionbase.h"

class JPlhConnectionBase : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JPlhConnectionBase(QTcpSocket* socket,QObject *parent = 0);
private:
	void dataProcess(const QByteArray &);
protected:
	virtual void afterPlh(const QByteArray&);
private:
	bool m_plh;
};

#endif // JPLHCONNECTIONBASE_H
