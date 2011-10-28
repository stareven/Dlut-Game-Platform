#include "network/jsocketbase.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QCoreApplication>

#include "global/jelapsedtimer.h"

/*!
	\defgroup client clientapi
	\brief 客户端的各种请求和通信
*/

/*!
	\file jsocketbase.h
	\brief 定义了 JSocketBase 类
*/

/*!
	\class JSocketBase jsocketbase.h network/jsocketbase.h
	\ingroup client
	\brief 客户端向服务器端发起连接请求及基本数据通信的基类
	
	\section base_protocol 基本通信协议
	在这个类中，定义了基本的通信协议。
	通过套接字发送数据的基本格式为：<MagicNumber::JMagicNumber:MagicNumber><qint32:size><byte[size]:data>
	  -# MagicNumber::JMagicNumber 类型，表示“魔数”（参见： MagicNumber ）。
	  -# qint32 类型，表示data的长度。
	  -# size个字节，表示数据的内容。数据内容的格式由协议自己制定。
	  
	关于qint32，请参见：Qt文档中关于qint32的内容：<a href="http://doc.qt.nokia.com/4.7/qtglobal.html#qint32-typedef" target="_blank">qint32-typedef</a>

	\sa JRequestBase MagicNumber
*/

/*!
	\fn JSocketBase::SocketCode(ENet netcode)
	\brief 当连接状态改变时发射此信号
	
	\sa ENet
*/

/*!
	\fn JSocketBase::SocketError(QString)
	\brief 以可读的字符串形式发送连接错误信号
*/

/*!
	\fn JSocketBase::dataProcess(const QByteArray&)
	\brief 数据处理函数
	
	子类需要重写这个函数以处理数据。
	
	\sa on_socket_readyRead()
*/

/*!
	\fn JSocketBase::getMagicNumber()const
	\brief 返回当前协议的“魔数”
	
	子类需要重写这个函数以定义当前协议的“魔数”。
	
	\sa MagicNumber
*/

/*!
	\brief 构造函数
	
	为啥每个类都有构造函数呢？\n
	关键是，它有就有呗，我还得给每个构造函数写文档。\n
	我就觉得，构造函数有啥文档可写的……\n
*/
JSocketBase::JSocketBase(QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->setObjectName("socket");
    QMetaObject::connectSlotsByName(this);
	m_size=0;
}

/*!
	\brief 连接服务器
	
	向地址为\a address 端口为\a port 发起连接。\n
	如果已经有连接，则断开当前连接，发起新连接。
*/
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

/*!
	\brief 是否已经连接
*/
bool JSocketBase::isConnected()const
{
    return m_socket->state()==QAbstractSocket::ConnectedState;
}

/*!
	\brief 当前的套接字状态
	
	参看 Qt4 的文档中关于 QAbstractSocket::SocketState 的内容。\n
	\sa QAbstractSocket::SocketState
*/
QAbstractSocket::SocketState JSocketBase::socketState () const
{
	return m_socket->state();
}

void JSocketBase::on_socket_connected()
{
    emit SocketCode(EN_CONNECTED);
}

void JSocketBase::on_socket_disconnected()
{
    emit SocketCode(EN_DISCONNECTED);
}

/*!
	\brief 接收但不处理数据

	当有数据到来的时候，这个函数处理数据长度与魔数。\n
	但它并不处理数据的内容而是将内容交给dataProcess()处理。\n

	\sa MagicNumber dataProcess()
*/
void JSocketBase::on_socket_readyRead()
{
    while(m_socket->bytesAvailable()>0)
    {
		if(m_size>0)
		{
			QByteArray readdata=m_socket->read(m_size-m_data.size());
			m_data+=readdata;
			if(m_data.size()==m_size)
			{
				dataProcess(m_data);
				m_data.clear();
				m_size=0;
			}
		}else if(m_socket->bytesAvailable()>=(qint64)(sizeof(int)+sizeof(MagicNumber::JMagicNumber))){
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
	qDebug()<<"JSocketBase::on_socket_error : "<<metaObject()->className()<<socketError;
	emit SocketError(m_socket->errorString());
}

/*!
	\brief 发送数据
	
	在数据\a data 前加上魔数和数据长度，之后发送。
*/
void JSocketBase::sendData(const QByteArray& data)
{
    if(m_socket->state()!=QAbstractSocket::ConnectedState)
    {
		qDebug()<<"JSocketBase::sendData : socket not connected ."<<metaObject()->className()<<m_socket->state();
    }
    qint32 size=data.size();
    QDataStream outsocketstream(m_socket);
	outsocketstream<<getMagicNumber();
    outsocketstream<<size;
    m_socket->write(data);
}
