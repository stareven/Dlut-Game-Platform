#ifndef JSNAKESERVERPROCESSOR_H
#define JSNAKESERVERPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

#include "jsnake.h"

class JRoomManager;
class QPoint;

class JSnakeServerProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JSnakeServerProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;
protected slots:
	void on_socket_disconnected();
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

#endif // JSNAKESERVERPROCESSOR_H
