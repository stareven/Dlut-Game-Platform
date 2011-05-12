#include "juserisonline.h"

QSet<JID> JUserIsOnline::g_onlineUsers;

bool JUserIsOnline::userGetOn(JID userid)
{
	if(userid<0) return false;
	if(g_onlineUsers.contains(userid)) return false;
	g_onlineUsers.insert(userid);
	return true;
}

bool JUserIsOnline::userGetOff(JID userid)
{
	if(userid<0) return false;
	if(!g_onlineUsers.contains(userid)) return false;
	return g_onlineUsers.remove(userid);
}

bool JUserIsOnline::userIsOnline(JID userid)const
{
	if(userid<0) return false;
	if(g_onlineUsers.contains(userid)) return true;
	else return false;
}
