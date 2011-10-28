#ifndef JREQUESTUSERINFO_H
#define JREQUESTUSERINFO_H

#include <QMap>

#include "jlhcrequestbase.h"
#include "global/userinfo.h"

#include "clientapi_global.h"

class JRequestUserInfoSocket;

class CLIENTAPISHARED_EXPORT JRequestUserInfo : public JLhcRequestBase
{
    Q_OBJECT
public:
    explicit JRequestUserInfo(QObject *parent = 0);
	UserInfo::SUserInfo rqsUserInfo(JID userId);
private:
	bool waitForUserInfo(JID userId,int msecs = 30000 )const;
private slots:
	void on_socket_rcvUserInfo(const UserInfo::SUserInfo&);
private:
	JRequestUserInfoSocket* m_socket;
	static QMap<JID,UserInfo::SUserInfo> s_userinfolist;
};

#endif // JREQUESTUSERINFO_H
