#include "jabstractdatabasefactory.h"

#include "textstream/jtextstreamdatabasefactory.h"
#include "sql/jsqldatabasefactory.h"

JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance(const QString& type)
{
	return JSQLDatabaseFactory::getInstance();
//	if(type =="textstream"){
//		return JTextStreamDatabaseFactory::getInstance();
//	}else if(type == "mysql"){
//		return NULL;
//	}
//	return NULL;
}
