#include "network/jconnectionbase.h"

#include <QTcpSocket>

/**
	\class JConnectionBase
	\brief 对Server端的基本的网络通信提供一个封装

	每当有连接到来时，Server端就会产生一个JConnectionBase（或它的子类）的实例来处理这个连接。
  */

/// \brief 构造函数
JConnectionBase::JConnectionBase(QTcpSocket* socket,QObject *parent) :
    QObject(parent),
    m_socket(socket)
{
    m_userid=-1;
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(on_socket_disconnected()));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(on_socket_readyRead()));
}

/**
	\brief 接收但不处理数据。

	当有数据到来的时候，这个函数处理数据长度与魔数。\n
	但它并不处理数据的内容而是将内容交给dataProcess()处理。\n

	\sa MagicNumber dataProcess()
*/
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
		}else if(m_socket->bytesAvailable()>=sizeof(int)+sizeof(MagicNumber::JMagicNumber)){
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

/**
	\brief 数据处理函数

	子类可以重写这个函数来处理数据。
*/
void JConnectionBase::dataProcess(const QByteArray& data)
{
    qDebug()<<"connection base : "<<data.size();
}

/**
	在数据\a data 前加上魔数和数据长度，之后发送。
*/
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

/**
	获取当前连接的客户端的用户ID。
*/
JID JConnectionBase::getUserId()const
{
	return m_userid;
}

void JConnectionBase::setUserId(JID userid)
{
	if(userid<0) return;
	m_userid=userid;
}
