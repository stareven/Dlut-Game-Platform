#ifndef JABSTRACTDATABASEFACTORY_H
#define JABSTRACTDATABASEFACTORY_H

#include <QObject>

class JAbsLoginDB;

class JAbstractDatabaseFactory : public QObject
{
protected:
	JAbstractDatabaseFactory(QObject *parent = 0);
public:
	static JAbstractDatabaseFactory* getInstance();
	virtual JAbsLoginDB* createLoginDB()=0;
};

#endif // JABSTRACTDATABASEFACTORY_H
