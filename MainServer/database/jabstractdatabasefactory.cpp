#include "jabstractdatabasefactory.h"

#include "jtextstreamdatabasefactory.h"

#include <QCoreApplication>

JAbstractDatabaseFactory::JAbstractDatabaseFactory(QObject *parent)
	:QObject(parent)
{
}

JAbstractDatabaseFactory* JAbstractDatabaseFactory::getInstance()
{
	static JAbstractDatabaseFactory* instance=new JTextStreamDatabaseFactory(QCoreApplication::instance());
	return instance;
}
