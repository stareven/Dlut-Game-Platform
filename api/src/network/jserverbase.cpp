#include "jserverbase.h"

#include <QTcpServer>

/*!
    \class JServerBase jserverbase.h <Socket/JServerBase>
    \ingroup socket
    \brief 服务器端基类

    处理基本的端口监听、连接等。 \n
*/

/*!
    \fn virtual void JServerBase::getConnection(QTcpSocket* socket,QObject* parent)const=0
    \brief 子类需要实现此抽象方法来处理连接。
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
    \brief 开始监听

    \a port 要求端口。\n
    如果 \a port 为0或 \a port 已被占用，则系统自动选择一个端口。
*/
quint16 JServerBase::run(quint16 port)
{
	if(!m_server->listen(QHostAddress::Any,port))
	{
		qDebug()<<"listen port:"<<port<<" failed. auto select port...";
		if(!m_server->listen(QHostAddress::Any,0))
		{
			qDebug()<<"auto select port failed. server is aborting .";
			return 0;
		}
	}
	return m_server->serverPort();
}

/*!
    \brief 返回当前正在监听的端口
*/
quint16 JServerBase::serverPort()const
{
	return m_server->serverPort();
}

void JServerBase::on_server_newConnection()
{
	while(m_server->hasPendingConnections())
	{
		QTcpSocket* socket=m_server->nextPendingConnection();
		JServerSocketBase *cnct=getConnection(socket,this);
		if(cnct==NULL)
		{
			qDebug()<<metaObject()->className()<<"create connection failed";
		}
	}
}
