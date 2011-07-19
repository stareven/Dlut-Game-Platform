#ifndef JSNAKECONNECTION_H
#define JSNAKECONNECTION_H

#include "network/jconnectionbase.h"
#include "jsnake.h"

class JRoomManager;
class QPoint;

class JSnakeConnection : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JSnakeConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray&);
	void on_socket_disconnected();
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
private:
	JRoomManager* m_roomMng;
private slots:
	void sendUserlist();
	void sendRoominfoUpdate(JID roomId);
	void sendRoominfoAdd(JID roomId);
	void sendRoominfoDelete(JID roomId);
	void sendRoomEnter(JID roomId,JID userId);
	void sendRoomEscape(JID roomId,JID userId);

	void sendGameAct_getReady(bool ready,int num);
	void sendGameAct_countDown(int sec);
	void sendGameAct_getCommand();
	void sendGameAct_turn(JSnake::EDire dire,int num);
	void sendGameAct_collision(int num);
	void sendGameAct_createBean(const QPoint& pt);
	void sendGameAct_increase(int num);
	void sendGameAct_moveOn(int num);
	void sendGameAct_Stop();
private:
	void processEnterRoom(JID roomId);
	void processEscapeRoom();
};

#endif // JSNAKECONNECTION_H
