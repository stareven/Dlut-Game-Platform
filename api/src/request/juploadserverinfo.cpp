#include "juploadserverinfo.h"

#include "../global/jserverinfo.h"

using namespace NetworkData;

JUploadServerInfo::JUploadServerInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadServerInfo::pushServerInfo(const JServerInfo& serverinfo,int msecs)
{
	return pushInformationData(serverinfo.getServerId(),serverinfo.toByteArray(),msecs);
}

JHead JUploadServerInfo::getHead(JID id)const
{
	return JServerInfo(id).head();
}
