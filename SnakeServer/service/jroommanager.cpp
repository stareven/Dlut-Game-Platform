#include "jroommanager.h"

JRoomManager JRoomManager::s_object;

JRoomManager::JRoomManager()
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

JCode JRoomManager::addRoom(const Snake::JRoom& room)
{
	if(m_rooms.contains(room.m_roomId))
	{
		return 1;
	}
	m_rooms.insert(room.m_roomId,room);
	emit roomAdded(room.m_roomId);
	return 0;
}

JCode JRoomManager::removeRoom(const Snake::JRoom& room)
{
	if(!m_rooms.contains(room.m_roomId))
	{
		return 1;
	}
	m_rooms.remove(room.m_roomId);
	emit roomRemoved(room.m_roomId);
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
