#include "jmainservercontrolroleprocessor.h"

#include "service/jpermissioncontrol.h"
#include "service/jcontrolrole.h"

#include <Session/JSession>
#include <Global/CodeError>

#include <QDataStream>

JMainServerControlRoleProcessor::JMainServerControlRoleProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerControlRoleProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID userId;
	JID role;
	JID act;
	stream>>userId;
	stream>>role;
	stream>>act;
	if(act >=0 && act <2 && role>=0 && role <=ROLE_ROOT ){
		processControlRole(userId,(ERole)role,(EControlRoleAction)act);
	}
}

JType JMainServerControlRoleProcessor::getProcessorType()const
{
	return EPI_ControlRole;
}

void JMainServerControlRoleProcessor::processControlRole(JID userId,ERole role,EControlRoleAction act)
{
	JPermissionControl pc(getSession()->getUserId());
	if(pc.checkControlRole(userId,role,act)){
		JControlRole cr;
		cr.execute(userId,role,act);
		replyResult(userId,ESuccess);
	}else{
		replyResult(userId,EPermissionDenied);
	}
}

void JMainServerControlRoleProcessor::replyResult(JID userId,JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<userId;
	outstream<<result;
	sendData(outdata);
}
