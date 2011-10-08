#ifndef JREQUESTUSERINFO_H
#define JREQUESTUSERINFO_H

#include "jinformationrequestbase.h"

#include "../global/juserinfo.h"

class JRequestUserInfo : public JInformationRequestBase
{
    Q_OBJECT
public:
    explicit JRequestUserInfo(QObject *parent = 0);
	JUserInfo rqsUserInfo(JID userId,JTime_t oldlimit,int msecs = 30000);
private:
//	bool waitForUserInfo(JID userId,int msecs = 30000 )const;
private slots:
//	void on_socket_rcvUserInfo(const JUserInfo&);
};

#endif // JREQUESTUSERINFO_H
