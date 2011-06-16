#include "jserverbase.h"

#include <QTcpServer>
#include <QCoreApplication>

#include "jgfsconnection.h"

JServerBase::JServerBase(QObject *parent) :
	QObject(parent)
{
    m_server=new QTcpServer(this);
    m_server->setObjectName("server");
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
            QCoreApplication::exit(3);
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
		JConnectionBase *cnct=new JGfsConnection(socket,this);
		if(cnct==NULL)
		{
			qDebug()<<"create connection failed";
		}
    }
}
