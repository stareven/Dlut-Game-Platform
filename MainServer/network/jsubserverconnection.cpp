#include "jsubserverconnection.h"

#include <QDataStream>

#include "service/jloginhash.h"
#include "ssubserver.h"

using namespace SubServer;

JSubServerConnection::JSubServerConnection(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
	m_passLoginHash=false;
}

void JSubServerConnection::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	switch((SubServer::EProtocol)protocol)
	{
	case SubServer::EP_LoginHash:
		{
			if(!m_passLoginHash)
			{
				JID userid;
				QByteArray crypro;
				JLoginHash::JCheck check;
				stream>>userid>>crypro;
				m_passLoginHash=(0==check.check(userid,crypro));
			}
			QByteArray outdata;
			QDataStream outstream(&outdata,QIODevice::WriteOnly);
			outstream<<(JID)SubServer::EP_LoginHash;
			outstream<<m_passLoginHash;
			sendData(outdata);
		}
		break;
	case SubServer::EP_ServerInfo:
		{
			if(!m_passLoginHash)
			{
				closeConnect();
				break;
			}
			SSubServer gi;
			stream>>gi.m_serverid;
			stream>>gi.m_name;
			stream>>gi.m_address;
			stream>>gi.m_port;
			stream>>(JID&)gi.m_type;
		}
		break;
	case SubServer::EP_Command:
		{
			//
		}
		break;
	}
}

void JSubServerConnection::on_socket_disconnected()
{
//    JGameInfoSrv::JGis4Admin gis;
//    gis.deleteGame(m_gameid);
	JConnectionBase::on_socket_disconnected();
}
