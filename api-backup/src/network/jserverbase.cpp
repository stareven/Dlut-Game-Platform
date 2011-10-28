#include "network/jserverbase.h"

#include <QTcpServer>
#include <QCoreApplication>

/*!
	\file jserverbase.h
	\brief 定义了 JServerBase 类
*/

/*!
	\class JServerBase jserverbase.h "network/jserverbase.h"
	\ingroup server
	\brief 对Server端的基本功能做了一个简单的封装
*/

/*!
	\fn JServerBase::getConnection(QTcpSocket* socket,QObject* parent)const
	\brief 返回一个 JConnectionBase 的实例来处理每一个连接的数据
*/

/*!
	\brief 构造函数
*/
JServerBase::JServerBase(QObject *parent) :
	QObject(parent)
{
	m_server=new QTcpServer(this);
    connect(m_server,SIGNAL(newConnection()),SLOT(on_server_newConnection()));
}

/*!
	\brief 启动一个Server
	
	尝试监听\a port 端口。
	\return Server的端口。
*/
quint16 JServerBase::run(quint16 port)
{
    if(!m_server->listen(QHostAddress::Any,port))
	{
        qDebug()<<"listen port:"<<port<<" failed. auto select port...";
        if(!m_server->listen(QHostAddress::Any,0))
        {
            qDebug()<<"auto select port failed. server is aborting .";
            QCoreApplication::exit(3);
        }
    }
    return m_server->serverPort();
}

/*!
	\brief 返回Server当前监听的端口
*/
quint16 JServerBase::serverPort()const
{
    return m_server->serverPort();
}

/*!
	\brief 处理新连接
	
	当有新连接到来的时候，这个函数会调用 getConnection() 函数产生一个 JConnectionBase 的实例来处理新连接。
	
	\sa getConnection()
*/
void JServerBase::on_server_newConnection()
{
    while(m_server->hasPendingConnections())
    {
		QTcpSocket* socket=m_server->nextPendingConnection();
		JConnectionBase *cnct=getConnection(socket,this);
		if(cnct==NULL)
		{
			qDebug()<<"create connection failed";
		}
    }
}
