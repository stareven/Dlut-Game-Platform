#include "jsnakesocket.h"

#include "jsnakeglobal.h"

JSnakeSocket JSnakeSocket::s_socket;

JSnakeSocket::JSnakeSocket(QObject *parent) :
    JSocketBase(parent)
{
}

JSnakeSocket& JSnakeSocket::getInstance()
{
	return s_socket;
}

void JSnakeSocket::sendHello(JID userId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Hello;
	outstream<<userId;
	sendData(outdata);
}

void JSnakeSocket::sendRqsUserlist()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Userlist;
	sendData(outdata);
}

void JSnakeSocket::sendAddRoom(const Snake::JRoom& room)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoominfoAdd;
	outstream<<room;
	sendData(outdata);
}

void JSnakeSocket::sendEnterRoom(JID roomId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoomEnter;
	outstream<<roomId;
	sendData(outdata);
}

void JSnakeSocket::sendEscapeRoom()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoomEscape;
	sendData(outdata);
}

void JSnakeSocket::sendRqsRoomlist()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Roomlist;
	sendData(outdata);
}

void JSnakeSocket::sendGA_Ready(bool ready)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Ready;
	outstream<<ready;
	sendData(outdata);
}

void JSnakeSocket::dataProcess(const QByteArray& data)
{
	using namespace SnakeProtocol;
	QDataStream stream(data);
	JProtocol protocol;
	stream>>protocol;
	switch(protocol)
	{
	case SP_Hello :
		{
			JCode code;
			stream>>code;
			emit rcvHello(code);
		}
		break;
	case SP_Roomlist :
		{
			QList<Snake::JRoom> roomlist;
			stream>>roomlist;
			emit rcvRoomlist(roomlist);
		}
		break;
	case SP_RoominfoUpdate :
		break;
	case SP_RoominfoAdd :
		{
			Snake::JRoom room;
			stream>>room;
			emit rcvAddRoom(room);
		}
		break;
	case SP_RoominfoDelete :
		{
			JID roomId;
			stream>>roomId;
			emit rcvDeleteRoom(roomId);
		}
		break;
	case SP_RoomAct :
		break;
	case SP_RoomEnter :
		{
			JID roomId,userId;
			stream>>roomId>>userId;
			emit rcvEnterRoom(roomId,userId);
		}
		break;
	case SP_RoomEscape :
		{
			JID roomId,userId;
			stream>>roomId>>userId;
			emit rcvEscapeRoom(roomId,userId);
		}
		break;
	case SP_Userlist :
		{
			JID roomId;
			QList<JID> userlist;
			stream>>roomId;
			stream>>userlist;
			emit rcvUserlist(roomId,userlist);
		}
		break;
	case SP_GA_Ready:
		{
			bool ready;
			int num;
			stream>>ready;
			stream>>num;
			emit rcvGA_Ready(ready,num);
		}
		break;
	}
}
