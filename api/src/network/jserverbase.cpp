#include "jserverbase.h"

#include <QTcpServer>

JServerBase::JServerBase(QObject *parent) :
    QObject(parent)
{
	m_server=new QTcpServer(this);
	connect(m_server,SIGNAL(newConnection()),SLOT(on_server_newConnection()));
}

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
