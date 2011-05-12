#include "jloginconnection.h"

#include <QByteArray>
#include <QDataStream>
//#include <QDebug>

#include "service/jloginverification.h"
#include "service/juserisonline.h"

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
    if(uio.userIsOnline(loginvrfc.getUserId())) code=EL_ALREADY_LOGIN;
    outstream<<code;
    if( 0 == code )
    {
        outstream<<loginvrfc.getUserId();
        outstream<<loginvrfc.getCrypro();
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
