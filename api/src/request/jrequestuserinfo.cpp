#include "jrequestuserinfo.h"

#include "../network/jinformation.h"

JRequestUserInfo::JRequestUserInfo(QObject *parent) :
	JInformationRequestBase(parent)
{
}

JUserInfo JRequestUserInfo::pullUserInfo(JID userId,int msecs)
{
	JUserInfo ui;
	ui.fromByteArray(pullInformationDataById(userId,msecs));
	return ui;
}

NetworkData::JHead JRequestUserInfo::getHeadById(JID id)const
{
	return JUserInfo(id).head();
}
