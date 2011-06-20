#include "jservertype.h"

#include "jconnectionfactory.h"

#include <QTcpServer>
#include <QCoreApplication>

JServerType::JServerType(EServerType st,QObject *parent) :
    QObject(parent),
    m_servertype(st)
{
    m_server=new QTcpServer(this);
    m_server->setObjectName("server");
    connect(m_server,SIGNAL(newConnection()),SLOT(on_server_newConnection()));
}

quint16 JServerType::run(quint16 port)
{
    if(!m_server->listen(QHostAddress::Any,port))
    {
//        return 0;
        qDebug()<<"listen port:"<<port<<" failed. auto select port...";
        if(!m_server->listen(QHostAddress::Any,0))
        {
            qDebug()<<"auto select port failed. server is aborting .";
            QCoreApplication::exit(3);
        }
    }
    return m_server->serverPort();
}

quint16 JServerType::serverPort()const
{
    return m_server->serverPort();
}

EServerType JServerType::serverType()const
{
    return m_servertype;
}

void JServerType::on_server_newConnection()
{
    while(m_server->hasPendingConnections())
    {
	QTcpSocket* socket=m_server->nextPendingConnection();
	JConnectionFactory cf;
	JConnectionBase *cnct=cf.createConnection(this->m_servertype,socket,this);
	if(cnct==NULL)
	{
	    qDebug()<<"create connection failed";
	}
    }
}
