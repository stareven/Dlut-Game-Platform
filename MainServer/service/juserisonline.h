#ifndef JUSERISONLINE_H
#define JUSERISONLINE_H

#include <QMap>

#include "global/jglobal.h"

class JUserIsOnline
{
private:
//	static QSet<JID> g_onlineUsers;
	static QMap<JID,quint16> s_onlineUsers;
public:
	void getOn(JID);
	void getOff(JID);
	quint16 count(JID)const;
	bool isOnline(JID)const;
};
#endif // JUSERISONLINE_H
