#include "jsnakeconnection.h"

#include <QDataStream>

#include "jsnakeglobal.h"
#include "service/juserlistmanager.h"

JSnakeConnection::JSnakeConnection(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
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
		break;
	case SP_RoominfoUpdate :
		break;
	case SP_RoominfoAdd :
		break;
	case SP_RoominfoDelete :
		break;
	case SP_Roomact :
		break;
	case SP_Roomenter :
		break;
	case SP_Roomescape :
		break;
	case SP_Userlist :
		{
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
		break;
	}
}

void JSnakeConnection::on_socket_disconnected()
{
	JUserlistManager ulm;
	ulm.removeUser(getUserId());
}
