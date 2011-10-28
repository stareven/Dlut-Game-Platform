#ifndef JLHCSOCKETBASE_H
#define JLHCSOCKETBASE_H

#include "jsocketbase.h"
#include "clientapi_global.h"

class CLIENTAPISHARED_EXPORT JLhcSocketBase : public JSocketBase
{
    Q_OBJECT
public:
    explicit JLhcSocketBase(QObject *parent = 0);
	void sendLoginHashCode(JID,const QByteArray&);
protected:
	void dataProcess(const QByteArray&);
	virtual void afterLhc(const QByteArray&)=0;
signals:
	void rcvLoginHashConfirm(bool);
private:
	bool m_lhc;
};

#endif // JLHCSOCKETBASE_H
