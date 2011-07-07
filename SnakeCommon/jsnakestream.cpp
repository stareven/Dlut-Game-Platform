#include <QString>
#include <QDataStream>

#include "jsnakeglobal.h"

QDataStream& operator>>(QDataStream& stream,Snake::JRoom& room)
{
	stream>>room.m_roomId;
	stream>>room.m_roomName;
	return stream;
}

QDataStream& operator<<(QDataStream& stream,const Snake::JRoom& room)
{
	stream<<room.m_roomId;
	stream<<room.m_roomName;
	return stream;
}
