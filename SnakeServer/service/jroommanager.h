#ifndef JROOMMANAGER_H
#define JROOMMANAGER_H

#include <QObject>
#include <QMap>

#include "jsnakeglobal.h"


class JRoomManager : public QObject
{
	Q_OBJECT
private:
	JRoomManager();
	static JRoomManager s_object;
public:
	static JRoomManager& getInstance();
	JCode updateRoom(const Snake::JRoom&);
	JCode addRoom(const Snake::JRoom&);
	JCode removeRoom(const Snake::JRoom&);
	Snake::JRoom getRoomInfo(JID roomId)const;
	QList<JID> getIdList()const;
	QList<Snake::JRoom> getRoomList()const;
signals:
	void roomUpdated(JID roomId);
	void roomAdded(JID roomId);
	void roomRemoved(JID roomId);
private:
	QMap<JID,Snake::JRoom> m_rooms;
};

#endif // JROOMMANAGER_H
