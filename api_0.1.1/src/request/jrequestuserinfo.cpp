#include "jrequestuserinfo.h"

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
