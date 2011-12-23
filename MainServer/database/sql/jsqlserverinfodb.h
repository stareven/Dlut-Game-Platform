#ifndef JSQLSERVERINFODB_H
#define JSQLSERVERINFODB_H

#include "../jabstractserverinfodb.h"

class QSqlDatabase;

class JSQLServerInfoDB : public JAbstractServerInfoDB
{
public:
	explicit JSQLServerInfoDB(QSqlDatabase *dgpDB, QObject *parent = 0);
//	~JSQLServerInfoDB();
	JServerInfo getServerInfoById(JID ID);
	JCode updateServerInfo(const JServerInfo &serverInfo);

private:
	QSqlDatabase *serverInfoDB;
};

#endif // JSQLSERVERINFODB_H
