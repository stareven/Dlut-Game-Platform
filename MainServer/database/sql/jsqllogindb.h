#ifndef JSQLLOGINDB_H
#define JSQLLOGINDB_H

#include "../jabstractlogindb.h"

class QSqlDatabase;

class JSQLLoginDB : public JAbstractLoginDB
{
public:
	explicit JSQLLoginDB(QSqlDatabase *dgpDB, QObject *parent = 0);
//	~JSQLLoginDB();
	JID checkLoginName(const QString &loginName);
	bool checkPasswd(JID userID, const QString &passwd);
	bool checkRole(JID userID, JID roleID);
	QString getLoginName(JID userID);
	QString getPassword(JID userID);
	JRoleCombination getRoleCombination(JID userID);
	JCode addLoginUser(const QString &loginName, const QString &passwd);
	void setRoleCombination(JID userID, JRoleCombination roles);

private:
	QSqlDatabase *loginDB;
};

#endif // JSQLLOGINDB_H
