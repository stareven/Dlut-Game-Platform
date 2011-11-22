#ifndef JHALLTALKBROADCASTER_H
#define JHALLTALKBROADCASTER_H

#include <QObject>

class JHallTalkBroadcaster : public QObject
{
    Q_OBJECT
	explicit JHallTalkBroadcaster(QObject *parent = 0);
public:
	static JHallTalkBroadcaster* getInstance();
signals:
	void rcvMessage(const QString& msg);
};

#endif // JHALLTALKBROADCASTER_H
