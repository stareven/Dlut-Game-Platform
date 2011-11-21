#ifndef JTEXTSTREAMUSERINFODB_H
#define JTEXTSTREAMUSERINFODB_H

#include "../jabstractuserinfodb.h"

class JTextStreamUserInfoDB : public JAbstractUserInfoDB
{
public:
	explicit JTextStreamUserInfoDB(QObject* parent=0);
	JUserInfo getUserInfoById(JID id);
	JCode updateUserInfo(const JUserInfo& userinfo);

	static void flush();
};

#endif // JTEXTSTREAMUSERINFODB_H
