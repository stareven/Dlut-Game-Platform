#include "juploaduserinfo.h"

#include "../global/juserinfo.h"

using namespace NetworkData;

JUploadUserInfo::JUploadUserInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadUserInfo::pushUserInfo(const JUserInfo& userinfo,int msecs)
{
	return pushInformationData(userinfo.getUserId(),userinfo.toByteArray(),msecs);
}

NetworkData::JHead JUploadUserInfo::getHead(JID id)const
{
	return JUserInfo(id).head();
}
