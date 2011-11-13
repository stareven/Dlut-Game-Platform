#include "jsnakeprocessor.h"

#include <QPoint>

#include "jsnakesocket.h"
#include "jsnakeglobal.h"

JSnakeProcessor::JSnakeProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JSnakeProcessor* JSnakeProcessor::getInstance()
{
	static JSnakeProcessor* instance=NULL;
	if(NULL == instance){
		JSnakeSocket* socket = JSnakeSocket::getInstance();
		JSession* session = socket->getSession();
		instance = new JSnakeProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JSnakeProcessor::sendHello(JID userId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Hello;
	outstream<<userId;
	sendData(outdata);
}

void JSnakeProcessor::sendRqsUserlist()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Userlist;
	sendData(outdata);
}

void JSnakeProcessor::sendAddRoom(const Snake::JRoom& room)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoominfoAdd;
	outstream<<room;
	sendData(outdata);
}

void JSnakeProcessor::sendEnterRoom(JID roomId)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoomEnter;
	outstream<<roomId;
	sendData(outdata);
}

void JSnakeProcessor::sendEscapeRoom()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_RoomEscape;
	sendData(outdata);
}

void JSnakeProcessor::sendRqsRoomlist()
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_Roomlist;
	sendData(outdata);
}

void JSnakeProcessor::sendGA_Ready(bool ready)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Ready;
	outstream<<ready;
	sendData(outdata);
}

void JSnakeProcessor::sendGA_Turn(qint16 dire)
{
	using namespace SnakeProtocol;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<SP_GA_Turn;
	outstream<<dire;
	sendData(outdata);
}

void JSnakeProcessor::process(const QByteArray& data)
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
		{
			Snake::JRoom roominfo;
			stream>>roominfo;
			qDebug()<<"SP_RoominfoUpdate:"<<roominfo.getRoomId();
			emit rcvRoominfoUpdate(roominfo);
		}
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
			qDebug()<<"SP_RoomEnter:"<<roomId<<userId;
			emit rcvEnterRoom(roomId,userId);
		}
		break;
	case SP_RoomEscape :
		{
			JID roomId,userId;
			stream>>roomId>>userId;
			qDebug()<<"SP_RoomEscape:"<<roomId<<userId;
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
	case SP_GA_CountDown:
		{
			int sec;
			stream>>sec;
			qDebug()<<"SP_GA_CountDown:"<<sec;
			emit rcvGA_CountDown(sec);
		}
		break;
	case SP_GA_GetCommand:
		qDebug()<<"SP_GA_GetCommand";
		emit rcvGA_GetCommand();
		break;
	case SP_GA_Turn:
		{
			qint16 dire;
			int num;
			stream>>dire;
			stream>>num;
			qDebug()<<"SP_GA_Turn:"<<dire<<num;
			emit rcvGA_Turn(dire,num);
		}
		break;
	case SP_GA_Collision:
		{
			int num;
			stream>>num;
			qDebug()<<"SP_GA_Collision:"<<num;
			emit rcvGA_Collision(num);
		}
		break;
	case SP_GA_CreateBean:
		{
			QPoint pt;
			stream>>pt;
			qDebug()<<"SP_GA_CreateBean:"<<pt;
			emit rcvGA_CreateBean(pt);
		}
		break;
	case SP_GA_Increase:
		{
			int num;
			stream>>num;
			qDebug()<<"SP_GA_Increase:"<<num;
			emit rcvGA_Increase(num);
		}
		break;
	case SP_GA_MoveOn:
		{
			int num;
			stream>>num;
			qDebug()<<"SP_GA_MoveOn:"<<num;
			emit rcvGA_MoveOn(num);
		}
		break;
	case SP_GA_Stop:
		qDebug()<<"SP_GA_Stop";
		emit rcvGA_Stop();
		break;
	}
}

EProcessorType JSnakeProcessor::getProcessorType()const
{
	return Snake::SnakeProcessorType;
}
