#include "juserinfoconnection.h"

#include <QDataStream>
#include <QDebug>

#include "database/juserinfodb.h"

JUserInfoConnection::JUserInfoConnection(QTcpSocket* socket,QObject *parent) :
	JPlhConnectionBase(socket,parent)
{
}

void JUserInfoConnection::afterPlh(const QByteArray& data)
{
	QDataStream stream(data);
	JID userId;
	stream>>userId;
	JUserInfoDb db;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<userId;
	outstream<<db.getUserInfo(userId);
	sendData(outdata);
}
