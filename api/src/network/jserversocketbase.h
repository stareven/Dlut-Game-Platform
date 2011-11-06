#ifndef JSERVERSOCKETBASE_H
#define JSERVERSOCKETBASE_H

#include "jsocketbase.h"

class JSession;

class JServerSocketBase : public JSocketBase
{
	Q_OBJECT
public:
	// 由JServerBase的子类作为工厂
	explicit JServerSocketBase(QTcpSocket* const socket,QObject *parent = 0);
    void closeConnect();
public:
	JSession* getSession()const;
private:
	JSession* m_session;
};

#endif // JSERVERSOCKETBASE_H
