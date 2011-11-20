#include "jmainserverloginprocessor.h"

#include <QDataStream>
#include <QDebug>

#include <Global/Login>
#include <Session/JSession>

#include "service/jloginverification.h"
#include "service/jloginhashcodecreator.h"
#include "service/juserstatemanager.h"
#include "service/jpermissioncontrol.h"

JMainServerLoginProcessor::JMainServerLoginProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JMainServerLoginProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	QString loginname;
	QString passwd;
	JID role;
	stream>>loginname>>passwd>>role;
	JLoginVerification lv;
	JCode code=lv.verification(loginname,passwd,(ERole)role);
	if(0==code){
		JUserStateManager usm;
		JPermissionControl pc(lv.getUserId());
		if(
				usm.getUserState(lv.getUserId())!=JUserStateManager::ES_OffLine
				&& !pc.isMultiLoginAble((ERole)role)){
			code = EL_ALREADY_LOGIN;
		}else{
			JLoginHashCodeCreator lhcc;
			lhcc.setUserId(lv.getUserId());
			getSession()->setUserId(lv.getUserId());
			getSession()->setLoginHashCode(lhcc.createLoginHashCode());
			usm.setUserState(lv.getUserId(),JUserStateManager::ES_OnLine);
		}
	}
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<code;
	if(0==code){
		outstream<<getSession()->getUserId();
		outstream<<getSession()->getLoginHashCode();
	}
	sendData(outdata);
}

EProcessorType JMainServerLoginProcessor::getProcessorType()const
{
	return EPI_LOGIN;
}
