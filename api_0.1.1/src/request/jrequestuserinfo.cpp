#include "jrequestuserinfo.h"

#include "jinformation.h"

JRequestUserInfo::JRequestUserInfo(QObject *parent) :
	JInformationRequestBase(parent)
{
}

JUserInfo JRequestUserInfo::pullUserInfo(JID userId,int msecs)
{
	JUserInfo ui;
	ui.fromByteArray(pullInformationData(userId,msecs));
	return ui;
}

NetworkData::JHead JRequestUserInfo::getHead(JID id)const
{
	return JUserInfo(id).head();
}
