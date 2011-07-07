#include "jroomlistmodel.h"

#include "network/jsnakesocket.h"

JRoomListModel::JRoomListModel(QObject *parent) :
    QAbstractListModel(parent)
{
	m_socket=&JSnakeSocket::getInstance();
	connect(m_socket,SIGNAL(rcvAddRoom(Snake::JRoom)),SLOT(on_socket_rcvAddRoom(Snake::JRoom)));
}

int JRoomListModel::rowCount(const QModelIndex&) const
{
	return m_rooms.count();
}

QVariant JRoomListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	 if (index.row() >= rowCount())
		return QVariant();

	 if (role == Qt::DisplayRole)
	 {
		JID roomId=m_index2Id.at(index.row());
		Snake::JRoom room=m_rooms.value(roomId);
		return QString("%1 %2").arg(room.m_roomId).arg(room.m_roomName);
		//return stringList.at(index.row());
	}
	 else
		return QVariant();

}

QVariant JRoomListModel::headerData(int section, Qt::Orientation orientation,
					 int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return QString("Column %1").arg(section);
	else
		return QString("Row %1").arg(section);
}

void JRoomListModel::on_socket_rcvAddRoom(const Snake::JRoom& room)
{
	m_index2Id.push_back(room.m_roomId);
	m_rooms.insert(room.m_roomId,room);
	int row=m_index2Id.size()-1;
	emit dataChanged(index(row),index(row));
}
