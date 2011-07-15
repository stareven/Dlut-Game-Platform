#ifndef JROOMLISTMODEL_H
#define JROOMLISTMODEL_H

#include <QAbstractListModel>

#include "jsnakeglobal.h"


class JSnakeSocket;

class JRoomListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JRoomListModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation,
						 int role = Qt::DisplayRole) const;
private:
	QList<JID> m_index2Id;
	QMap<JID,Snake::JRoom> m_rooms;
	JSnakeSocket* m_socket;
private slots:
	void on_socket_rcvAddRoom(const Snake::JRoom&);
	void on_socket_rcvRoomList(const QList<Snake::JRoom>& roomlist);
	void on_socket_rcvDeleteRoom(JID roomId);
};

#endif // JROOMLISTMODEL_H
