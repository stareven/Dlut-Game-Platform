#include "jrequestuserinfo.h"

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

JUserInfo JRequestUserInfo::getUserInfo(JID userId)
{
	JUserInfo ui;
	ui.fromByteArray(getInformationDataById(userId));
	return ui;
}

NetworkData::JHead JRequestUserInfo::getHeadById(JID id)const
{
	return JUserInfo(id).head();
}
