#ifndef JUSERLISTMANAGER_H
#define JUSERLISTMANAGER_H

#include "global/jglobal.h"
#include <QList>

class JUserlistManager
{
public:
    JUserlistManager();
	JID getRoomByUser(JID userId)const;
	QList<JID> getUserlistInRoom(JID roomId)const;
	JCode addUser(JID userId,JID roomId);
	JCode moveUser(JID userId,JID roomId);
};

#endif // JUSERLISTMANAGER_H
