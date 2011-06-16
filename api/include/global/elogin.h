#ifndef ELOGIN_H
#define ELOGIN_H

#include <QString>
#include <QObject>

enum ELogin{
	EL_SUCCESS,			//from server
	EL_NO_SUCH_USER,
	EL_PASSWD_WRONG,
	EL_NO_SUCH_ROLE,
	EL_ALREADY_LOGIN,
	EL_CONNECTED,		//local network
	EL_SOCKET_CAN_NOT_WRITE,
	EL_SOCKET_DISCONNECTED,
	EL_BEGIN_TO_LOGIN,
};

const QString loginMsg[]={
	QObject::tr("login success"),
	QObject::tr("no such user"),
	QObject::tr("password wrong"),
	QObject::tr("no such role"),
	QObject::tr("already login"),
	QObject::tr("connected"),
	QObject::tr("socket can not write"),
	QObject::tr("socket disconnected"),
	QObject::tr("begin to login"),
};

#endif
