#include "jtextstreamdatabasefactory.h"

#include <QCoreApplication>

#include "jtextstreamlogindb.h"
#include "jtextstreamuserinfodb.h"
#include "jtextstreamgameinfodb.h"
#include "jtextstreamserverinfodb.h"

JTextStreamDatabaseFactory::JTextStreamDatabaseFactory(QObject *parent)
	:JAbstractDatabaseFactory(parent)
{
}

JTextStreamDatabaseFactory::~JTextStreamDatabaseFactory()
{
	JTextStreamLoginDB::flush();
	JTextStreamUserInfoDB::flush();
	JTextStreamGameInfoDB::flush();
	JTextStreamServerInfoDB::flush();
}

JTextStreamDatabaseFactory* JTextStreamDatabaseFactory::getInstance()
{
	static JTextStreamDatabaseFactory* instance=new JTextStreamDatabaseFactory(QCoreApplication::instance());
	return instance;
}

JAbstractLoginDB* JTextStreamDatabaseFactory::createLoginDB()
{
	return new JTextStreamLoginDB(this);
}

JAbstractUserInfoDB* JTextStreamDatabaseFactory::createUserInfoDB()
{
	return new JTextStreamUserInfoDB(this);
}

JAbstractGameInfoDB* JTextStreamDatabaseFactory::createGameInfoDB()
{
	return new JTextStreamGameInfoDB(this);
}

JAbstractServerInfoDB* JTextStreamDatabaseFactory::createServerInfoDB()
{
	return new JTextStreamServerInfoDB(this);
}
