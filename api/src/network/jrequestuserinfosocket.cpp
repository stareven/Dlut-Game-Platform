#include "network/jrequestuserinfosocket.h"

#include <QDataStream>

#include "global/userinfo.h"

JRequestUserInfoSocket::JRequestUserInfoSocket(QObject *parent) :
    JPlhSocketBase(parent)
{
}

void JRequestUserInfoSocket::rqsUserInfo(JID userId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<userId;
	sendData(outdata);
}

void JRequestUserInfoSocket::afterPlh(const QByteArray& data)
{
	QDataStream stream(data);
	JID userId;
	UserInfo::SUserInfo userinfo;
	stream>>userId;
	stream>>userinfo;
	qDebug()<<"JRequestUserInfoSocket rcv userinfo"<<userId<<userinfo.m_userId<<userinfo.m_nickname;
	emit rcvUserInfo(userinfo);
}
