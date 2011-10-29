#ifndef JUSERISONLINE_H
#define JUSERISONLINE_H

#include <QMap>

#include <Global/Global>

class JUserIsOnline
{
private:
	static QMap<JID,quint16> s_onlineUsers;
public:
	void getOn(JID);
	void getOff(JID);
	quint16 count(JID)const;
	bool isOnline(JID)const;
};
#endif // JUSERISONLINE_H
