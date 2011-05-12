#ifndef JABSLOGINDB_H
#define JABSLOGINDB_H

#include "jglobal.h"

class JAbsLoginDB
{
public:
    JAbsLoginDB();
    virtual JID checkLoginName(const QString& loginname);
    virtual bool checkPasswd(JID,const QString& passwd);
    virtual bool checkRole(JID,JID);
};

#endif // JABSLOGINDB_H
