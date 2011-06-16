#include "jconnectionbase.h"

#include <QTcpSocket>

//#include "service/jloginhash.h"
//#include "service/juserisonline.h"

JConnectionBase::JConnectionBase(QTcpSocket* socket,QObject *parent) :
    QObject(parent),
    m_socket(socket)
{
    m_userid=-1;
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(on_socket_disconnected()));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(on_socket_readyRead()));
}

void JConnectionBase::on_socket_readyRead()
{
    static int size=0;
    while(m_socket->bytesAvailable()>0)
    {
        if(size>0)
        {
			QByteArray data=m_socket->read(size);
			size=0;
			dataProcess(data);
        }else if(m_socket->bytesAvailable()>=sizeof(int)){//size==0
            QDataStream stream(m_socket);
            stream>>size;
        }
    }
}

void JConnectionBase::on_socket_disconnected()
{
	qDebug()<<"JConnectionBase::on_socket_disconnected";
//    JLoginHash::JDelete del;
//    JUserIsOnline uio;
//    del.del(m_userid);
//    uio.userGetOff(m_userid);
}

void JConnectionBase::dataProcess(const QByteArray& data)
{
    qDebug()<<"connection base : "<<data.size();
}

void JConnectionBase::sendData(const QByteArray& data)
{
    int size=data.size();
    QDataStream outsocketstream(m_socket);
    outsocketstream<<size;
    m_socket->write(data);
}

void JConnectionBase::closeConnect()
{
    m_socket->disconnectFromHost();
}

JID JConnectionBase::getUserId()const
{
	return m_userid;
}

void JConnectionBase::setUserId(JID userid)
{
	if(userid<0) return;
	m_userid=userid;
}
