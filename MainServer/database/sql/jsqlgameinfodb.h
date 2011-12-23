#ifndef JSQLGAMEINFODB_H
#define JSQLGAMEINFODB_H

#include "../jabstractgameinfodb.h"

class QSqlDatabase;

class JSQLGameInfoDB : public JAbstractGameInfoDB
{
public:
	explicit JSQLGameInfoDB(QSqlDatabase *dgpDB, QObject *parent = 0);
//	~JSQLGameInfoDB();
	JGameInfo getGameInfoById(JID ID);
	JGameList getGameList();
	JCode updateGameInfo(const JGameInfo &gameInfo);

private:
	QSqlDatabase *gameInfoDB;

};

#endif // JSQLGAMEINFODB_H
