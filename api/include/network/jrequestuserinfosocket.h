#ifndef JREQUESTUSERINFOSOCKET_H
#define JREQUESTUSERINFOSOCKET_H

#include "jlhcsocketbase.h"

namespace UserInfo
{
	class SUserInfo;
}

class JRequestUserInfoSocket : public JLhcSocketBase
{
    Q_OBJECT
public:
    explicit JRequestUserInfoSocket(QObject *parent = 0);
	void rqsUserInfo(JID userId);
protected:
	void afterLhc(const QByteArray&);
signals:
	void rcvUserInfo(const UserInfo::SUserInfo&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_GetUserInfo;
	}
};

#endif // JREQUESTUSERINFOSOCKET_H
