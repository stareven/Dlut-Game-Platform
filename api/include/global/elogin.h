#ifndef ELOGIN_H
#define ELOGIN_H

#include <QString>
#include <QObject>

typedef qint16 JRole;
enum ERole{
	ROLE_GAMEPLAYER,
	ROLE_GAMEDESIGNER,
	ROLE_GAMESERVERRUNNER,
	ROLE_ADMIN,
	ROLE_ROOT
};

enum ELogin{
	EL_SUCCESS,			//from server
	EL_NO_SUCH_USER,
	EL_PASSWD_WRONG,
	EL_NO_SUCH_ROLE,
	EL_ALREADY_LOGIN,
	EL_SOCKET_DISCONNECTED,
};

const QString loginMsg[]={
	QObject::tr("login success"),
	QObject::tr("no such user"),
	QObject::tr("password wrong"),
	QObject::tr("no such role"),
	QObject::tr("already login"),
	QObject::tr("socket disconnected"),
};

#endif
