#ifndef JSNAKEPROCESSOR_H
#define JSNAKEPROCESSOR_H

#include <Processor/JClientNetworkDataProcessorBase>

namespace Snake
{
	class JRoom;
}
class QPoint;

class JSnakeProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JSnakeProcessor(JSession* session,JSocketBase *socket);
public:
	static JSnakeProcessor* getInstance();
	void sendHello(JID userId);
	void sendRqsUserlist();
	void sendAddRoom(const Snake::JRoom&);
	void sendEnterRoom(JID roomId);
	void sendEscapeRoom();
	void sendRqsRoomlist();
	void sendGA_Ready(bool ready);
	void sendGA_Turn(qint16 dire);
signals:
	void rcvHello(JCode code);
	void rcvUserlist(JID roomId,const QList<JID>& userlist);
	void rcvAddRoom(const Snake::JRoom&);
	void rcvDeleteRoom(JID roomId);
	void rcvEnterRoom(JID roomId,JID userId);
	void rcvEscapeRoom(JID roomId,JID userId);
	void rcvRoomlist(const QList<Snake::JRoom>& roomlist);
	void rcvRoominfoUpdate(const Snake::JRoom& roominfo);
	void rcvGA_Ready(bool ready,int num);
	void rcvGA_CountDown(int sec);
	void rcvGA_GetCommand();
	void rcvGA_Turn(qint16 dire,int num);
	void rcvGA_Collision(int num);
	void rcvGA_CreateBean(const QPoint& pt);
	void rcvGA_Increase(int num);
	void rcvGA_MoveOn(int num);
	void rcvGA_Stop();
public:
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
};

#endif // JSNAKEPROCESSOR_H
