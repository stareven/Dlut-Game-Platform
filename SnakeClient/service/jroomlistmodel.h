#ifndef JROOMLISTMODEL_H
#define JROOMLISTMODEL_H

#include <QAbstractListModel>

#include "jsnakeglobal.h"


class JSnakeProcessor;

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
	JSnakeProcessor* m_processor;
private slots:
	void on_processor_rcvAddRoom(const Snake::JRoom&);
	void on_processor_rcvRoomList(const QList<Snake::JRoom>& roomlist);
	void on_processor_rcvDeleteRoom(JID roomId);
	void on_processor_rcvRoominfoUpdate(const Snake::JRoom& roominfo);
};

#endif // JROOMLISTMODEL_H
