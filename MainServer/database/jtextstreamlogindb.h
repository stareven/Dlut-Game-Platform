#ifndef JTEXTSTREAMLOGINDB_H
#define JTEXTSTREAMLOGINDB_H

#include "jabslogindb.h"

class JTextStreamLoginDB : public JAbsLoginDB
{
public:
    explicit JTextStreamLoginDB(QObject *parent = 0);
	JID checkLoginName(const QString& loginname);
	bool checkPasswd(JID,const QString& passwd);
	bool checkRole(JID,JID);
};

#endif // JTEXTSTREAMLOGINDB_H
