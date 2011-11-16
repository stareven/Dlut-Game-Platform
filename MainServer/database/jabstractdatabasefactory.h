#ifndef JABSTRACTDATABASEFACTORY_H
#define JABSTRACTDATABASEFACTORY_H

#include <QObject>

#include "jabstractlogindb.h"
#include "jabstractuserinfodb.h"
#include "jabstractgameinfodb.h"
#include "jabstractserverinfodb.h"

class JAbstractDatabaseFactory : public QObject
{
protected:
	explicit JAbstractDatabaseFactory(QObject *parent = 0);
public:
	static JAbstractDatabaseFactory* getInstance(const QString& type="textstream");
	virtual JAbstractLoginDB* createLoginDB()=0;
	virtual JAbstractUserInfoDB* createUserInfoDB()=0;
	virtual JAbstractGameInfoDB* createGameInfoDB()=0;
	virtual JAbstractServerInfoDB* createServerInfoDB()=0;
};

#endif // JABSTRACTDATABASEFACTORY_H
