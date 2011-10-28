#ifndef JUSERINFOCONNECTION_H
#define JUSERINFOCONNECTION_H

#include "jplhconnectionbase.h"

class JUserInfoConnection : public JPlhConnectionBase
{
    Q_OBJECT
public:
	explicit JUserInfoConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void afterPlh(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_GetUserInfo;
	}
};

#endif // JUSERINFOCONNECTION_H
