#include "jabslogindb.h"

#include <QString>
#include "global/elogin.h"

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

static const SLoginUser loginusers[]={
    {109,"elephant","acm",(1<<ROLE_GAMEPLAYER)},
    {241,"jdmd","jdmd",(1<<ROLE_ADMIN) | (1<<ROLE_ROOT) },
    {794,"lixiaopang","lxp",(1<<ROLE_GAMEDESIGNER) | (1<<ROLE_ADMIN) },
    {900,"sampleplayer","123",(1<<ROLE_GAMEPLAYER)},
    {901,"sampledesigner","123",(1<<ROLE_GAMEDESIGNER)},
    {902,"sampleserverrunner","123",(1<<ROLE_GAMESERVERRUNNER)},
    {903,"sampleadmin","123",(1<<ROLE_ADMIN)},
	{904,"sampleroot","123",(1<<ROLE_ROOT)},
	{1001,"debug1","1",(1<<ROLE_GAMEPLAYER)},
	{1002,"debug2","1",(1<<ROLE_GAMEPLAYER)},
	{1003,"debug3","1",(1<<ROLE_GAMEPLAYER)},
	{1004,"debug4","1",(1<<ROLE_GAMEPLAYER)},
	{1005,"debug5","1",(1<<ROLE_GAMEPLAYER)},
	{1006,"debug6","1",(1<<ROLE_GAMEPLAYER)},
};
static const int NUM_USER=sizeof(loginusers)/sizeof(SLoginUser);

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
