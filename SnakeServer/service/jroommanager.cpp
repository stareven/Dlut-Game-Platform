#include "jroommanager.h"

JRoomManager JRoomManager::s_object;

JRoomManager::JRoomManager(QObject* parent)
	:QObject(parent)
{
}

JRoomManager& JRoomManager::getInstance()
{
	return s_object;
}

JCode JRoomManager::updateRoom(const Snake::JRoom& room)
{
	m_rooms[room.m_roomId]=room;
	emit roomUpdated(room.m_roomId);
	return 0;
}

JCode JRoomManager::addRoom(Snake::JRoom& room)
{
	if(m_rooms.contains(room.m_roomId))
	{
		return 1;
	}
	if(room.m_roomId<0)
	{
		JID i;
		for(i=1;i<MAX_ROOM;++i)
		{
			if(!m_rooms.contains(i))
			{
				room.m_roomId=i;
				m_rooms.insert(room.m_roomId,room);
				emit roomAdded(room.m_roomId);
				return 0;
			}
		}
		return 2;
	}
	m_rooms.insert(room.m_roomId,room);
	emit roomAdded(room.m_roomId);
	return 0;
}

JCode JRoomManager::removeRoom(JID roomId)
{
	if(!m_rooms.contains(roomId))
	{
		return 1;
	}
	m_rooms.remove(roomId);
	emit roomRemoved(roomId);
	return 0;
}

JCode JRoomManager::enterRoom(JID roomId,JID userId)
{
	if(!m_rooms.contains(roomId))
	{
		return 1;
	}
	if(m_rooms[roomId].m_players.size()>=Snake::Max_Players)
	{
		return 2;
	}
	m_rooms[roomId].m_players.insert(userId);
	emit roomEnter(roomId,userId);
	return 0;
}

Snake::JRoom JRoomManager::getRoomInfo(JID roomId)const
{
	return m_rooms.value(roomId);
}

QList<JID> JRoomManager::getIdList()const
{
	return m_rooms.keys();
}

QList<Snake::JRoom> JRoomManager::getRoomList()const
{
	return m_rooms.values();
}
