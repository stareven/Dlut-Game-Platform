#include "jabstractdatabasefactory.h"

#include "jtextstreamdatabasefactory.h"

JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance(const QString& type)
{
	if(type =="textstream"){
		return JTextStreamDatabaseFactory::getInstance();
	}else if(type == "mysql"){
		return NULL;
	}
	return NULL;
}
