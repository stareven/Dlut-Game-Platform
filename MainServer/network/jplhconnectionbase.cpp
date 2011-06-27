#include "jplhconnectionbase.h"

#include <QDebug>
#include <QDataStream>

#include "service/jloginhash.h"

JPlhConnectionBase::JPlhConnectionBase(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
	m_plh=false;
}

void JPlhConnectionBase::dataProcess(const QByteArray& data)
{
	if(m_plh)
	{
		afterPlh(data);
	}else{
		QDataStream stream(data);
		JID userid;
		QByteArray crypro;
		JLoginHash lh;
		stream>>userid>>crypro;
		qDebug()<<"plh:"<<userid<<crypro.toHex().toUpper();
		JCode plhCode=lh.check (userid,crypro);
		m_plh=(0==plhCode);
		qDebug()<<"plh:"<<m_plh;
		QByteArray outdata;
		QDataStream outstream(&outdata,QIODevice::WriteOnly);
		outstream<<m_plh;
		qDebug()<<"plh: send";
		sendData(outdata);
		if(!m_plh) closeConnect();
		setUserId(userid);
	}
}

void JPlhConnectionBase::afterPlh(const QByteArray& data)
{
	qDebug()<<"JPlhConnectionBase::afterPlh:"<<data.size();
}
