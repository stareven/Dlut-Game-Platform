#include "jservertype.h"

#include "jconnectionfactory.h"

#include <QTcpServer>
#include <QCoreApplication>

JServerType::JServerType(EServerType st,QObject *parent) :
	JServerBase(parent),
    m_servertype(st)
{
    m_server=new QTcpServer(this);
    m_server->setObjectName("server");
    connect(m_server,SIGNAL(newConnection()),SLOT(on_server_newConnection()));
}

EServerType JServerType::serverType()const
{
    return m_servertype;
}

JConnectionBase* JServerType::getConnection(QTcpSocket* socket,
											QObject* parent)const
{
	JConnectionFactory cf;
	return cf.createConnection(this->m_servertype,socket,parent);
}
