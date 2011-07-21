#include "network/jconnectionbase.h"

#include <QTcpSocket>

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
        }else if(m_socket->bytesAvailable()>=sizeof(int)){
            QDataStream stream(m_socket);
			MagicNumber::JMagicNumber mn;
			stream>>mn;
            stream>>size;
			if(mn != getMagicNumber())
			{
				qDebug()<<"magic number error:"<<metaObject()->className()<<mn<<getMagicNumber();
			}
        }
    }
}

void JConnectionBase::on_socket_disconnected()
{
	qDebug()<<"JConnectionBase::on_socket_disconnected"<<metaObject()->className();
}

void JConnectionBase::dataProcess(const QByteArray& data)
{
    qDebug()<<"connection base : "<<data.size();
}

void JConnectionBase::sendData(const QByteArray& data)
{
    int size=data.size();
    QDataStream outsocketstream(m_socket);
	outsocketstream<<getMagicNumber();
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
