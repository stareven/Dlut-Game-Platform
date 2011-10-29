#ifndef JTEXTSTREAMDATABASEFACTORY_H
#define JTEXTSTREAMDATABASEFACTORY_H

#include "jabstractdatabasefactory.h"

class JTextStreamDatabaseFactory : public JAbstractDatabaseFactory
{
public:
	JTextStreamDatabaseFactory(QObject *parent = 0);
	JAbsLoginDB* createLoginDB();
};

#endif // JTEXTSTREAMDATABASEFACTORY_H
