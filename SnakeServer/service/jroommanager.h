#ifndef JROOMMANAGER_H
#define JROOMMANAGER_H

#include <QObject>
#include <QMap>

#include "jsnakeglobal.h"

const JID MAX_ROOM=65535;

class JRoomManager : public QObject
{
	Q_OBJECT
private:
	explicit JRoomManager(QObject* parent=0);
	static JRoomManager s_object;
public:
	static JRoomManager& getInstance();
	JCode updateRoom(const Snake::JRoom&);
	JCode addRoom(Snake::JRoom&);
	JCode removeRoom(JID roomId);
	JCode enterRoom(JID roomId,JID userId);
	Snake::JRoom getRoomInfo(JID roomId)const;
	QList<JID> getIdList()const;
	QList<Snake::JRoom> getRoomList()const;
signals:
	void roomUpdated(JID roomId);
	void roomAdded(JID roomId);
	void roomRemoved(JID roomId);
	void roomEnter(JID roomId,JID userId);
private:
	QMap<JID,Snake::JRoom> m_rooms;
};

#endif // JROOMMANAGER_H
