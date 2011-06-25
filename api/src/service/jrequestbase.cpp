#include "service/jrequestbase.h"

#include <QCoreApplication>

#include "network/jsocketbase.h"
#include "global/jelapsedtimer.h"

const static QString error_no="no error";
JRequestBase::JRequestBase(QObject *parent)
	:QObject(parent)
{
	m_socket=NULL;
	m_state=ECS_Init;
	m_error=&error_no;
}

void JRequestBase::connectToHost(const QHostAddress& address,quint16 port)
{
	if(m_socket==NULL)
	{
		qDebug()<<"JRequestBase: socket is NULL";
		m_state=ECS_Error;
		const static QString error_socket_null="socket is NULL";
		m_error=&error_socket_null;
		return;
	}
	m_socket->connectToHost(address,port);
	m_state=ECS_Connecting;
}

JRequestBase::EConnectState JRequestBase::getConnectState()const
{
	return m_state;
}

bool JRequestBase::waitForConnected(int msecs)const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getConnectState()!=ECS_Connecting)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getConnectState()==ECS_Connected;
}

const QString& JRequestBase::error()const
{
	return *m_error;
}

void JRequestBase::setSocket(JSocketBase* socket)
{
	m_socket=socket;
	connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
}

void JRequestBase::on_socket_SocketCode(JCode code)
{
	switch((ENet)code)
	{
	case EN_CONNECTED:
		m_state=ECS_Connected;
		m_error=&error_no;
		break;
	case EN_DISCONNECTED:
		m_state=ECS_Connected;
		{
			const static QString error_disconnected="disconnected";
			m_error=&error_disconnected;
		}
		break;
	}
}
