#include "jrequestcontrolrole.h"

#include <QCoreApplication>

#include "../network/jclientcontrolroleprocessor.h"
#include "../global/jelapsedtimer.h"
#include "../global/jcodeerror.h"

JRequestControlRole::JRequestControlRole(QObject *parent) :
    JRequestBase(parent)
{
	m_processor = JClientControlRoleProcessor::getInstance();
	m_sendError = ESuccess;
	m_state = ESCRS_Init;
	connect(m_processor,
			SIGNAL(receiveControlRoleResult(JID,JCode)),
			SLOT(on_processor_receiveControlRoleResult(JID,JCode)));
}

void JRequestControlRole::sendControlRole(JID userId,ERole role,EControlRoleAction act)
{
	m_state = ESCRS_Sending;
	m_processor->sendControlRole(userId,role,act);
}

JRequestControlRole::ESendControlRoleState JRequestControlRole::getSendControlRoleState()const
{
	return m_state;
}

bool JRequestControlRole::waitForSended(int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getSendControlRoleState()!=ESCRS_Sending)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getSendControlRoleState()==ESCRS_Success;
}

const QString& JRequestControlRole::getSendError()const
{
	static const QString success = tr("no error");
	static const QString permissiondenied = tr("permission denied");
	static const QString nosuchuser = tr("no such user");
	static QString unknowerror;
	switch(m_sendError){
	case ESuccess:
		return success;
		break;
	case EPermissionDenied:
		return permissiondenied;
		break;
	case ENoSuchUser:
		return nosuchuser;
		break;
	default:
		unknowerror = tr("unknow error:%1").arg(m_sendError);
		return unknowerror;
		break;
	}
	unknowerror = tr("unknow error:%1").arg(m_sendError);
	return unknowerror;
}

void JRequestControlRole::on_processor_receiveControlRoleResult(JID userId,JCode result)
{
	switch(result){
	case ESuccess:
		m_state = ESCRS_Success;
		break;
	default:
		m_state = ESCRS_Failed;
		break;
	}
	m_sendError = result;
	emit receiveControlRoleResult(userId,result);
}
