#include "network/jlhcsocketbase.h"

#include <QDataStream>

JLhcSocketBase::JLhcSocketBase(QObject *parent) :
    JSocketBase(parent)
{
	m_lhc=false;
}

void JLhcSocketBase::sendLoginHashCode(JID id,const QByteArray& code)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<id;
	outstream<<code;
	sendData(outdata);
}

void JLhcSocketBase::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	if(m_lhc)
	{
		afterLhc(data);
	}else{
		stream>>m_lhc;
		emit rcvLoginHashConfirm(m_lhc);
	}
}
