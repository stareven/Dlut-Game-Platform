#include "network/jplhsocketbase.h"

#include <QDataStream>

JPlhSocketBase::JPlhSocketBase(QObject *parent) :
    JSocketBase(parent)
{
	m_plh=false;
}

void JPlhSocketBase::sendCrypro(JID id,const QByteArray& crypro)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<id;
	outstream<<crypro;
	sendData(outdata);
}

void JPlhSocketBase::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	if(m_plh)
	{
		afterPlh(data);
	}else{
		stream>>m_plh;
		emit rcvPassLoginHash(m_plh);
	}
}
