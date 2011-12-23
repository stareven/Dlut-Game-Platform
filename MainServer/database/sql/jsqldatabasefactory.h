#ifndef JSQLDATABASEFACTORY_H
#define JSQLDATABASEFACTORY_H

#include "../jabstractdatabasefactory.h"

class QSqlDatabase;
class QSettings;

class JSQLDatabaseFactory : public JAbstractDatabaseFactory
{
	explicit JSQLDatabaseFactory(QObject *parent = 0);
public:
	~JSQLDatabaseFactory();
	static JSQLDatabaseFactory *getInstance();
	JAbstractLoginDB *createLoginDB();
	JAbstractUserInfoDB *createUserInfoDB();
	JAbstractGameInfoDB *createGameInfoDB();
	JAbstractServerInfoDB *createServerInfoDB();

private:
	//static int connectCount;
	QSqlDatabase *dgpDB;
	QSettings *dgpdbIni;
};

#endif // JSQLDATABASEFACTORY_H
