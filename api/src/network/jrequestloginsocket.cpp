#include "network/jrequestloginsocket.h"

#include <QTcpSocket>
#include <QHostAddress>
#include "global/elogin.h"

JRequestLoginSocket::JRequestLoginSocket(QObject *parent) :
	JSocketBase(parent)
{
}

void JRequestLoginSocket::login(const QString& loginname,const QString& passwd,const JID& role)
{
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<role;
	sendData(data);
}

void JRequestLoginSocket::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	JCode code;
	stream>>code;
	if(code==0)
	{
		stream>>m_userid>>m_crypro;
	}
	emit loginCode(code);
}

JID JRequestLoginSocket::getUserId()const
{
    return m_userid;
}

const QByteArray& JRequestLoginSocket::getCrypro()const
{
    return m_crypro;
}
