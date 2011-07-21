#include "jloginconnection.h"

#include <QByteArray>
#include <QDataStream>

#include "service/jloginverification.h"
#include "service/juserisonline.h"
#include "service/jloginhash.h"

JLoginConnection::JLoginConnection(QTcpSocket* socket,QObject *parent) :
    JConnectionBase(socket,parent)
{
}

void JLoginConnection::dataProcess(const QByteArray& data)
{
    QDataStream stream(data);
    QString loginname,passwd;
    JID role;
    stream>>loginname>>passwd;
    stream>>role;
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    JLoginVerification loginvrfc;
    JCode code=loginvrfc.verification(loginname,passwd,role);
    JUserIsOnline uio;
	if(role!=ROLE_GAMESERVERRUNNER && uio.isOnline(loginvrfc.getUserId())) code=EL_ALREADY_LOGIN;
    outstream<<code;
    if( 0 == code )
    {
		JLoginHash lh;
		lh.add(loginvrfc.getUserId(),data);
        outstream<<loginvrfc.getUserId();
		outstream<<lh.get(loginvrfc.getUserId());
        setUserId(loginvrfc.getUserId());
		uio.getOn(loginvrfc.getUserId());
    }
    sendData(outdata);
}

void JLoginConnection::on_socket_disconnected()
{
	JLoginHash lh;
	JUserIsOnline uio;
	uio.getOff(getUserId());
	if(!uio.isOnline(getUserId()))
	{
		lh.del(getUserId());
	}

}
