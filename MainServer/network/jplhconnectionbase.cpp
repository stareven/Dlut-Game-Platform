#include "jplhconnectionbase.h"

#include <QDebug>

#include "service/jloginhash.h"

JPlhConnectionBase::JPlhConnectionBase(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
}

void JPlhConnectionBase::dataProcess(const QByteArray& data)
{
	static bool plh=false;
	if(plh)
	{
		afterPlh(data);
	}else{
		QDataStream stream(data);
		JID userid;
		QByteArray crypro;
		JLoginHash::JCheck check;
		stream>>userid>>crypro;
		plh=(0==check.check(userid,crypro));
		QByteArray outdata;
		QDataStream outstream(&outdata,QIODevice::WriteOnly);
		outstream<<plh;
		sendData(outdata);
	}
}

void JPlhConnectionBase::afterPlh(const QByteArray& data)
{
	qDebug()<<"JPlhConnectionBase::afterPlh:"<<data.size();
}
