#include "network/jsocketbase.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QCoreApplication>

#include "global/jelapsedtimer.h"

JSocketBase::JSocketBase(QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->setObjectName("socket");
    QMetaObject::connectSlotsByName(this);
	m_size=0;
}

void JSocketBase::connectToHost(const QHostAddress& address,
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

bool JSocketBase::isConnected()const
{
    //qDebug()<<m_socket->state();
    return m_socket->state()==QAbstractSocket::ConnectedState;
}

void JSocketBase::on_socket_connected()
{
    emit SocketCode(EN_CONNECTED);
}

void JSocketBase::on_socket_disconnected()
{
    emit SocketCode(EN_DISCONNECTED);
}

void JSocketBase::on_socket_readyRead()
{
    //qDebug()<<"JSocketBase::on_socket_readyRead";
//    static int size=0;
    while(m_socket->bytesAvailable()>0)
    {
		if(m_size>0)
		{
			QByteArray readdata=m_socket->read(m_size-m_data.size());
			m_data+=readdata;
			qDebug()<<"size="<<m_size<<"read data size="<<m_data.size();
			if(m_data.size()==m_size)
			{
				dataProcess(m_data);
				m_data.clear();
				m_size=0;
			}
        }else if(m_socket->bytesAvailable()>=sizeof(int)){//size==0
            QDataStream stream(m_socket);
			MagicNumber::JMagicNumber mn;
			stream>>mn;
			stream>>m_size;
			if(mn != getMagicNumber())
			{
				qDebug()<<"magic number error:"<<metaObject()->className()<<mn<<getMagicNumber();
			}
        }
    }
}

void JSocketBase::on_socket_error ( QAbstractSocket::SocketError socketError )
{
    qDebug()<<"JSocketBase::on_socket_error : "<<socketError;
}

void JSocketBase::sendData(const QByteArray& data)
{
//    QElapsedTimer t;
//    t.start();
//    bool connected=false;
//    int elapse=1000;
//    while(t.elapsed()<elapse)
//    {
//        if(m_socket->state()==QAbstractSocket::ConnectedState)
//        {
//            connected=true;
//            break;
//        }
//        QCoreApplication::processEvents();
//    }
//    if(!connected)
//    {
//        qDebug()<<"JSocketBase::sendData : socket not connected wait for "<<elapse<<" msec .";
//        return;
//    }
    if(m_socket->state()!=QAbstractSocket::ConnectedState)
    {
        qDebug()<<"JSocketBase::sendData : socket not connected .";
    }
    int size=data.size();
    QDataStream outsocketstream(m_socket);
	outsocketstream<<getMagicNumber();
    outsocketstream<<size;
    m_socket->write(data);
}

QAbstractSocket::SocketState JSocketBase::socketState()const
{
	return m_socket->state();
}
