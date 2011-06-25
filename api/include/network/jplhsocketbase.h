#ifndef JPLHSOCKETBASE_H
#define JPLHSOCKETBASE_H

#include "jsocketbase.h"

class JPlhSocketBase : public JSocketBase
{
    Q_OBJECT
public:
    explicit JPlhSocketBase(QObject *parent = 0);
	void sendCrypro(JID,const QByteArray&);
protected:
	void dataProcess(const QByteArray&);
	virtual void afterPlh(const QByteArray&)=0;
signals:
	void rcvPassLoginHash(bool);
private:
	bool m_plh;
};

#endif // JPLHSOCKETBASE_H
