#include <QString>
#include <QDataStream>

#include "jsnakeglobal.h"

QDataStream& operator>>(QDataStream& stream,Snake::JRoom& room)
{
	stream>>room.m_roomId;
	stream>>room.m_roomName;
	for(int i=0;i<Snake::Max_Players;++i)
	{
		stream>>room.m_players[i];
	}
	return stream;
}

QDataStream& operator<<(QDataStream& stream,const Snake::JRoom& room)
{
	stream<<room.m_roomId;
	stream<<room.m_roomName;
	for(int i=0;i<Snake::Max_Players;++i)
	{
		stream<<room.m_players[i];
	}
	return stream;
}
