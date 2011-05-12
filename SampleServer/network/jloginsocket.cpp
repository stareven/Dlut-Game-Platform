#include "jloginsocket.h"

#include <QTcpSocket>
#include <QHostAddress>
#include "elogin.h"

JLoginSocket::JLoginSocket(QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->setObjectName("socket");
    QMetaObject::connectSlotsByName(this);
}

void JLoginSocket::login(const QString& loginname,const QString& passwd,const JID& role)
{
    if(!m_socket->isWritable())
    {
	emit loginCode(JCode(EL_SOCKET_CAN_NOT_WRITE));
	return;
    }
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<role;
    int size=data.size();
    QDataStream outstream(m_socket);
    outstream<<size;
    m_socket->write(data);
}

void JLoginSocket::connectToHost(const QHostAddress& address,
		    quint16 port)
{
    if(m_socket->state()==QAbstractSocket::ConnectedState)
    {
	if(m_socket->peerAddress()==address && m_socket->peerPort()==port)
	{
	    on_socket_connected();
	    return;
	}else{
	    m_socket->disconnectFromHost();
	}
    }
    m_socket->connectToHost(address,port);
}

void JLoginSocket::on_socket_connected()
{
    emit loginCode(EL_CONNECTED);
    //qDebug()<<"JLoginSocket::on_socket_connected";
}

void JLoginSocket::on_socket_disconnected()
{
    emit loginCode(JCode(EL_SOCKET_DISCONNECTED));
}

void JLoginSocket::on_socket_readyRead()
{
    static int size=0;
    while(m_socket->bytesAvailable()>0)
    {
	if(size>0)
	{
	    //qDebug()<<"size="<<size;
	    QByteArray data=m_socket->read(size);
	    size=0;
	    QDataStream stream(data);
	    JCode code;
	    stream>>code;
	    if(code==0)
            {
                stream>>m_userid>>m_crypro;
                qDebug()<<"userid = "<<m_userid<<" crypro="<<m_crypro.toHex().toUpper();
	    }
            emit loginCode(code);
	}else if(m_socket->bytesAvailable()>=sizeof(int)){//size==0
	    QDataStream stream(m_socket);
	    stream>>size;
	}
    }
}

JID JLoginSocket::getUserId()const
{
    return m_userid;
}

const QByteArray& JLoginSocket::getCrypro()const
{
    return m_crypro;
}
