#include "juserisonline.h"

QMap<JID,quint16> JUserIsOnline::s_onlineUsers;

void JUserIsOnline::getOn(JID id)
{
	s_onlineUsers[id]++;
}

void JUserIsOnline::getOff(JID id)
{
	if(--s_onlineUsers[id])
	{
		s_onlineUsers.remove(id);
	}
}

quint16 JUserIsOnline::count(JID id)const
{
	return s_onlineUsers.value(id);
}

bool JUserIsOnline::isOnline(JID id)const
{
	return count(id)>0;
}
