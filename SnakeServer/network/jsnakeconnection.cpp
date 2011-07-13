#include "jsnakeconnection.h"

#include <QDataStream>

#include "jsnakeglobal.h"
#include "service/juserlistmanager.h"
#include "service/jroommanager.h"

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
		{
			JID roomId;
			stream>>roomId;
			m_roomMng->removeRoom(roomId);
		}
		break;
	case SP_RoomAct :
		break;
	case SP_RoomEnter :
		{
			JID roomId;
			stream>>roomId;
			processEnterRoom(roomId);
		}
		break;
	case SP_RoomEscape :
		break;
	case SP_Userlist :
		sendUserlist();
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

void JSnakeConnection::processEnterRoom(JID roomId)
{
	JID userId=getUserId();
	JUserlistManager ulm;
	JID formerRoomId=ulm.getRoomByUser(userId);
	if(formerRoomId!=0) return;
	Q_ASSERT(0==ulm.moveUser(userId,roomId));
	Q_ASSERT(0==m_roomMng->enterRoom(roomId,userId));
	sendUserlist();
}
