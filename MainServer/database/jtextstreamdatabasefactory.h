#ifndef JTEXTSTREAMDATABASEFACTORY_H
#define JTEXTSTREAMDATABASEFACTORY_H

#include "jabstractdatabasefactory.h"

class JTextStreamDatabaseFactory : public JAbstractDatabaseFactory
{
	explicit JTextStreamDatabaseFactory(QObject *parent = 0);
public:
	~JTextStreamDatabaseFactory();
	static JTextStreamDatabaseFactory* getInstance();
	JAbstractLoginDB* createLoginDB();
	JAbstractUserInfoDB* createUserInfoDB();
	JAbstractGameInfoDB* createGameInfoDB();
	JAbstractServerInfoDB* createServerInfoDB();
};

#endif // JTEXTSTREAMDATABASEFACTORY_H
