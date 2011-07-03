#include "jsnakesocket.h"

#include "jsnakeglobal.h"

JSnakeSocket::JSnakeSocket(QObject *parent) :
    JSocketBase(parent)
{
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
			JID roomId;
			QList<JID> userlist;
			stream>>roomId;
			stream>>userlist;
			emit rcvUserlist(roomId,userlist);
		}
		break;
	}
}
