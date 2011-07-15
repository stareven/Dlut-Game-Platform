#include "jsnakeconnection.h"

#include <QDataStream>
#include <QDebug>

#include "jsnakeglobal.h"
#include "service/juserlistmanager.h"
#include "service/jroommanager.h"
#include "service/jsnakegameonserver.h"

JSnakeConnection::JSnakeConnection(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
	m_roomMng=&JRoomManager::getInstance();
	connect(m_roomMng,SIGNAL(roomAdded(JID)),SLOT(sendRoominfoAdd(JID)));
	connect(m_roomMng,SIGNAL(roomRemoved(JID)),SLOT(sendRoominfoDelete(JID)));
	connect(m_roomMng,SIGNAL(roomUpdated(JID)),SLOT(sendRoominfoUpdate(JID)));
	connect(m_roomMng,SIGNAL(roomEnter(JID,JID)),SLOT(sendRoomEnter(JID,JID)));
}

void JSnakeConnection::dataProcess(const QByteArray& data)
{
	using namespace SnakeProtocol;
	QDataStream stream(data);
	JProtocol protocol;
	stream>>protocol;
	switch(protocol)
	{
	case SP_Hello :
		{
			JID userId;
			stream>>userId;
			setUserId(userId);
			JCode code;
			JUserlistManager ulm;
			code=ulm.addUser(userId,0);
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<SP_Hello;
			outstream<<code;
			sendData(outdata);
		}
		break;
	case SP_Roomlist :
		{
			QList<Snake::JRoom> roomlist;
			roomlist=m_roomMng->getRoomList();
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<SP_Roomlist;
			outstream<<roomlist;
			sendData(outdata);
		}
		break;
	case SP_RoominfoUpdate :
		{
			JID roomId;
			stream>>roomId;
			sendRoominfoUpdate(roomId);
		}
		break;
	case SP_RoominfoAdd :
		{
			Snake::JRoom roominfo;
			stream>>roominfo;
			JCode code=m_roomMng->addRoom(roominfo);
			if(0==code)
			{
//				sendRoomEnter(roominfo.m_roomId);
				processEnterRoom(roominfo.getRoomId());
			}
			/*{
				sendRoominfoAdd(roominfo.m_roomId);
			}
			signal has connected to the slot , so it can send roominfo add automatically.
			*/
		}
		break;
	case SP_RoominfoDelete :
		// 客户端不应该有删除房间的权力。
		qDebug()<<"SP_RoominfoDelete : clinet will never send this .";
		break;
	case SP_RoomAct :
		qDebug()<<"SP_RoomAct : clinet will never send this .";
		break;
	case SP_RoomEnter :
		{
			JID roomId;
			stream>>roomId;
			processEnterRoom(roomId);
		}
		break;
	case SP_RoomEscape :
		{
			processEscapeRoom();
		}
		break;
	case SP_Userlist :
		sendUserlist();
		break;
	case SP_GameAct:
		qDebug()<<"SP_GameAct : clinet will never send this .";
		break;
	case SP_GA_Ready:
		{
			bool ready;
			stream>>ready;
			JUserlistManager ulm;
			JID roomId;
			roomId=ulm.getRoomByUser(getUserId());
			JSnakeGameOnServer *game=m_roomMng->getGame(roomId);
			Q_ASSERT(game!=NULL);
			Snake::JRoom room=m_roomMng->getRoomInfo(roomId);
			game->ready(ready,room.getPositionById(getUserId()));
		}
		break;
	case SP_GA_CountDown:
		qDebug()<<"SP_GA_CountDown : clinet will never send this .";
		break;
	case SP_GA_GetCommand:
		qDebug()<<"SP_GA_GetCommand : clinet will never send this .";
		break;
	case SP_GA_Turn:
		{
			qint16 dire;
			stream>>dire;
			JUserlistManager ulm;
			JID roomId;
			roomId=ulm.getRoomByUser(getUserId());
			JSnakeGameOnServer *game=m_roomMng->getGame(roomId);
			Q_ASSERT(game!=NULL);
			Snake::JRoom room=m_roomMng->getRoomInfo(roomId);
			game->setTurn((JSnake::EDire)dire,room.getPositionById(getUserId()));
		}
		break;
	case SP_GA_Collision:
		qDebug()<<"SP_GA_Collision : clinet will never send this .";
		break;
	case SP_GA_CreateBean:
		qDebug()<<"SP_GA_CreateBean : clinet will never send this .";
		break;
	case SP_GA_Increase:
		qDebug()<<"SP_GA_Increase : clinet will never send this .";
		break;
	case SP_GA_MoveOn:
		qDebug()<<"SP_GA_MoveOn : clinet will never send this .";
		break;
	}
}

void JSnakeConnection::on_socket_disconnected()
{
	JUserlistManager ulm;
	ulm.removeUser(getUserId());
}

void JSnakeConnection::sendUserlist()
{
	using namespace SnakeProtocol;
	JUserlistManager ulm;
	JID roomId;
	roomId=ulm.getRoomByUser(getUserId());
	QList<JID> userlist=ulm.getUserlistInRoom(roomId);
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Userlist;
	outstream<<roomId;
	outstream<<userlist;
	sendData(outdata);
}

void JSnakeConnection::sendRoominfoUpdate(JID roomId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoominfoUpdate;
	outstream<<m_roomMng->getRoomInfo(roomId);
	sendData(outdata);
}

void JSnakeConnection::sendRoominfoAdd(JID roomId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoominfoAdd;
	outstream<<m_roomMng->getRoomInfo(roomId);
	sendData(outdata);
}

void JSnakeConnection::sendRoominfoDelete(JID roomId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoominfoDelete;
	outstream<<roomId;
	sendData(outdata);
}

void JSnakeConnection::sendRoomEnter(JID roomId,JID userId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoomEnter;
	outstream<<roomId;
	outstream<<userId;
	outstream<<(JCode)0;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_getReady(bool ready,int num)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Ready;
	outstream<<ready;
	outstream<<num;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_countDown(int sec)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_CountDown;
	outstream<<sec;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_getCommand()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_GetCommand;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_turn(JSnake::EDire dire,int num)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Turn;
	outstream<<(qint16)dire;
	outstream<<num;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_collision(int num)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Collision;
	outstream<<num;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_createBean(const QPoint& pt)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_CreateBean;
	outstream<<pt;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_increase(int num)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Increase;
	outstream<<num;
	sendData(outdata);
}

void JSnakeConnection::sendGameAct_moveOn(int num)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_MoveOn;
	outstream<<num;
	sendData(outdata);
}

void JSnakeConnection::processEnterRoom(JID roomId)
{
	JID userId=getUserId();
	JUserlistManager ulm;
	JID formerRoomId=ulm.getRoomByUser(userId);
	if(formerRoomId!=0) return;
	Q_ASSERT(0==ulm.moveUser(userId,roomId));
	Q_ASSERT(0==m_roomMng->enterRoom(roomId,userId));
	JSnakeGameOnServer *game=m_roomMng->getGame(roomId);
	connect(game,SIGNAL(getReady(bool,int)),SLOT(sendGameAct_getReady(bool,int)));
	connect(game,SIGNAL(countDown(int)),SLOT(sendGameAct_countDown(int)));
	connect(game,SIGNAL(getCommand()),SLOT(sendGameAct_getCommand()));
	connect(game,SIGNAL(turn(JSnake::EDire,int)),SLOT(sendGameAct_turn(JSnake::EDire,int)));
	connect(game,SIGNAL(collision(int)),SLOT(sendGameAct_collision(int)));
	connect(game,SIGNAL(createBean(const QPoint&)),SLOT(sendGameAct_createBean(const QPoint&)));
	connect(game,SIGNAL(increase(int)),SLOT(sendGameAct_increase(int)));
	connect(game,SIGNAL(moveOn(int)),SLOT(sendGameAct_moveOn(int)));
	sendUserlist();
}

void JSnakeConnection::processEscapeRoom()
{
	JID userId=getUserId();
	JUserlistManager ulm;
	JID formerRoomId=ulm.getRoomByUser(userId);
	if(formerRoomId==0) return;
	Q_ASSERT(0==ulm.moveUser(userId,0));
	Q_ASSERT(0==m_roomMng->escapeRoom(formerRoomId,userId));
	JSnakeGameOnServer *game=m_roomMng->getGame(formerRoomId);
	game->disconnect(this);
	sendUserlist();
}


