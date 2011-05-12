#include "jabslogindb.h"

#include <QString>

JAbsLoginDB::JAbsLoginDB()
{
}

struct SLoginUser
{
    JID m_userid;
    QString m_loginname;
    QString m_passwd;
    JRole m_role;
};

static const int NUM_USER=3;
static const SLoginUser loginusers[NUM_USER]={
    {109,"elephant","acm",ROLE_GAMEPLAYER},
    {241,"jdmd","jdmd",ROLE_ADMIN | ROLE_ROOT },
    {794,"lixiaopang","lxp",ROLE_GAMEDESIGNER | ROLE_ADMIN }
};

JID JAbsLoginDB::checkLoginName(const QString& loginname)
{
    for(int i=0;i<NUM_USER;++i)
    {
	if(loginusers[i].m_loginname==loginname)
	{
	    return loginusers[i].m_userid;
	}
    }
    return -1;
}

bool JAbsLoginDB::checkPasswd(JID userid,const QString& passwd)
{
    int i;
    for(i=0;i<NUM_USER;++i)
    {
	if(loginusers[i].m_userid==userid)
	{
	    break;
	}
    }
    if(i<0 || i >= NUM_USER) return false;
    if(loginusers[i].m_passwd==passwd) return true;
    else return false;
}

bool JAbsLoginDB::checkRole(JID userid,JID role)
{
    int i;
    for(i=0;i<NUM_USER;++i)
    {
	if(loginusers[i].m_userid==userid)
	{
	    break;
	}
    }
    if(i<0 || i >= NUM_USER) return false;
    if(loginusers[i].m_role & (1<<role) ) return true;
    else return false;
}
