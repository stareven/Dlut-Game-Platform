#include "jgamelist.h"

#include <QDataStream>

using namespace NetworkData;

JGameList::JGameList()
	:JSerializableData(-1)
{
}

void JGameList::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	stream>>*this;
}

QByteArray JGameList::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<*this;
	return data;
}

JHead JGameList::head()const
{
	return JHead(-1,EIT_GameInfo,1);
}
