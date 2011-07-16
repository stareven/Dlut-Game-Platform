#ifndef JSNAKESOCKET_H
#define JSNAKESOCKET_H

#include "network/jsocketbase.h"

namespace Snake
{
	class JRoom;
}

class JSnakeSocket : public JSocketBase
{
    Q_OBJECT
	explicit JSnakeSocket(QObject *parent = 0);
	static JSnakeSocket s_socket;
public:
	static JSnakeSocket& getInstance();
	void sendHello(JID userId);
	void sendRqsUserlist();
	void sendAddRoom(const Snake::JRoom&);
	void sendEnterRoom(JID roomId);
	void sendEscapeRoom();
	void sendRqsRoomlist();
	void sendGA_Ready(bool ready);
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
protected:
	void dataProcess(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
};

#endif // JSNAKESOCKET_H
