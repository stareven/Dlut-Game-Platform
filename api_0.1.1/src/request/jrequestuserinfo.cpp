#include "jrequestuserinfo.h"

JRequestUserInfo::JRequestUserInfo(QObject *parent) :
	JInformationRequestBase(parent)
{
}

JUserInfo JRequestUserInfo::rqsUserInfo(JID userId,JTime_t oldlimit,int msecs)
{
	JUserInfo rtn;
	NetworkData::JHead head=rtn.head(userId);
	if(rqsModifyTime(head,oldlimit)){
		waitForModifyTime(head,msecs/2);
	}
	if(rqsInfomationData(head,oldlimit)){
		waitForInfomationData(head,msecs/2);
	}
	rtn.fromByteArray(this->getInfomationData(head));
	return rtn;
}
