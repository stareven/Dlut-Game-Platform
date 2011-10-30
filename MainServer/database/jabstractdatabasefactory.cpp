#include "jabstractdatabasefactory.h"

#include "jtextstreamdatabasefactory.h"



JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance()
{
	return JTextStreamDatabaseFactory::getInstance();
}
