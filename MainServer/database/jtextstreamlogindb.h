#ifndef JTEXTSTREAMLOGINDB_H
#define JTEXTSTREAMLOGINDB_H

#include "jabstractlogindb.h"

class JTextStreamLoginDB : public JAbstractLoginDB
{
public:
    explicit JTextStreamLoginDB(QObject *parent = 0);
	JID checkLoginName(const QString& loginname);
	bool checkPasswd(JID,const QString& passwd);
	bool checkRole(JID,JID);

	static void flush();
};

#endif // JTEXTSTREAMLOGINDB_H
