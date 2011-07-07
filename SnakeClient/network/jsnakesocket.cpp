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
		break;
	case SP_RoomAct :
		break;
	case SP_RoomEnter :
		break;
	case SP_RoomEscape :
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
	}
}
