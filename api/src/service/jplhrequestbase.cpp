#include "service/jplhrequestbase.h"

#include <QCoreApplication>

#include "network/jplhsocketbase.h"
#include "global/jelapsedtimer.h"

JPlhRequestBase::JPlhRequestBase(QObject *parent) :
    JRequestBase(parent)
{
	m_socket=NULL;
	m_state=EPS_Init;
}

void JPlhRequestBase::sendCrypro(JID id,const QByteArray& crypro)
{
	if(m_socket==NULL)
	{
		qDebug()<<"JRequestBase: socket is NULL";
		return;
	}
	m_socket->sendCrypro(id,crypro);
	m_state=EPS_Sending;
}

JPlhRequestBase::EPlhState JPlhRequestBase::getPlhState()const
{
	return m_state;
}

bool JPlhRequestBase::waitForPlh(int msecs )const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getPlhState()!=EPS_Sending)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getPlhState()==EPS_Success;
}

void JPlhRequestBase::setSocket(JPlhSocketBase* socket)
{
	m_socket=socket;
	JRequestBase::setSocket(socket);
}

void JPlhRequestBase::on_socekt_rcvPassLoginHash(bool plh)
{
	if(plh)
	{
		m_state=EPS_Success;
	}else{
		m_state=EPS_Failed;
	}
}
