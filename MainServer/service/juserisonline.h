#ifndef JUSERISONLINE_H
#define JUSERISONLINE_H

#include <QSet>

#include "jglobal.h"

class JUserIsOnline
{
private:
	static QSet<JID> g_onlineUsers;
public:
	bool userGetOn(JID);
	bool userGetOff(JID);
	bool userIsOnline(JID)const;
};
#endif // JUSERISONLINE_H
