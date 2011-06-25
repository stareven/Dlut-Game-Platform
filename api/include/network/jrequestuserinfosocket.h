#ifndef JREQUESTUSERINFOSOCKET_H
#define JREQUESTUSERINFOSOCKET_H

#include "jplhsocketbase.h"

namespace UserInfo
{
	class SUserInfo;
}

class JRequestUserInfoSocket : public JPlhSocketBase
{
    Q_OBJECT
public:
    explicit JRequestUserInfoSocket(QObject *parent = 0);
	void rqsUserInfo(JID userId);
protected:
	void afterPlh(const QByteArray&);
signals:
	void rcvUserInfo(const UserInfo::SUserInfo&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_GetUserInfo;
	}
};

#endif // JREQUESTUSERINFOSOCKET_H
