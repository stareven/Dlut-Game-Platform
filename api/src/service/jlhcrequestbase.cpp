#include "service/jlhcrequestbase.h"

#include <QCoreApplication>

#include "network/jlhcsocketbase.h"
#include "global/jelapsedtimer.h"

JLhcRequestBase::JLhcRequestBase(QObject *parent) :
    JRequestBase(parent)
{
	m_socket=NULL;
	m_state=EPS_Init;
}

void JLhcRequestBase::sendLoginHashCode(JID id,const QByteArray& code)
{
	if(m_socket==NULL)
	{
                qDebug()<<"JLhcRequestBase: socket is NULL";
		return;
	}
	if(EPS_Success==m_state)
	{
		qDebug()<<"already plh";
		return;
	}
	m_state=EPS_Sending;
        m_socket->sendLoginHashCode(id,code);
}

JLhcRequestBase::ELhcState JLhcRequestBase::getLhcState()const
{
	return m_state;
}

bool JLhcRequestBase::waitForLhc(int msecs )const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
                if(getLhcState()!=EPS_Sending)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
        return getLhcState()==EPS_Success;
}

void JLhcRequestBase::setSocket(JLhcSocketBase* socket)
{
	m_socket=socket;
        connect(m_socket,SIGNAL(rcvLoginHashConfirm(bool)),SLOT(on_socket_rcvLoginHashConfirm(bool)));
	JRequestBase::setSocket(socket);
}

void JLhcRequestBase::on_socket_rcvLoginHashConfirm(bool lhc)
{
        if(lhc)
	{
		m_state=EPS_Success;
	}else{
		m_state=EPS_Failed;
	}
        emit lhcResult(lhc);
}
