#include "jtextstreamdatabasefactory.h"

#include "jtextstreamlogindb.h"

JTextStreamDatabaseFactory::JTextStreamDatabaseFactory(QObject *parent)
	:JAbstractDatabaseFactory(parent)
{
}

JAbsLoginDB* JTextStreamDatabaseFactory::createLoginDB()
{
	return new JTextStreamLoginDB(this);
}
