#include "jloginconnection.h"

#include <QByteArray>
#include <QDataStream>
//#include <QDebug>

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
    //send back : id , logincrypto ,
    //qDebug()<<loginname<<passwd<<role;
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    JLoginVerification loginvrfc;
    JCode code=loginvrfc.verification(loginname,passwd,role);
    JUserIsOnline uio;
    if(role!=ROLE_GAMESERVERRUNNER && uio.userIsOnline(loginvrfc.getUserId())) code=EL_ALREADY_LOGIN;
    outstream<<code;
    if( 0 == code )
    {
		JLoginHash::JAdd add;
		add.add(loginvrfc.getUserId(),data);
		JLoginHash::JGet get;
        outstream<<loginvrfc.getUserId();
		outstream<<get.get(loginvrfc.getUserId());
        setUserId(loginvrfc.getUserId());
        uio.userGetOn(loginvrfc.getUserId());
    }
    sendData(outdata);
//    int size=outdata.size();
//    QDataStream outsocketstream(socket);
//    outsocketstream<<size;
//    //socket->write(QByteArray::number(size));
//    socket->write(outdata);
}

void JLoginConnection::on_socket_disconnected()
{
	JLoginHash::JDelete del;
	JUserIsOnline uio;
	del.del(getUserId());
	uio.userGetOff(getUserId());
}
