#ifndef JSQLUSERINFODB_H
#define JSQLUSERINFODB_H

#include "../jabstractuserinfodb.h"

class QSqlDatabase;

class JSQLUserInfoDB : public JAbstractUserInfoDB
{
public:
	explicit JSQLUserInfoDB(QSqlDatabase *dgpDB, QObject *parent = 0);
//	~JSQLUserInfoDB();
	JUserInfo getUserInfoById(JID userID);
	JCode updateUserInfo(const JUserInfo &userInfo);
	void testUserinfoExist(JID userID);

private:
	QSqlDatabase *userInfoDB;
};

#endif // JSQLUSERINFODB_H
