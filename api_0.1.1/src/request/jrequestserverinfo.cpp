#include "jrequestserverinfo.h"

using namespace NetworkData;

JRequestServerInfo::JRequestServerInfo(QObject *parent) :
    JInformationRequestBase(parent)
{
}

JServerInfo JRequestServerInfo::pullServerInfo(JID serverId,int msecs )
{
	JServerInfo si(serverId);
	si.fromByteArray(pullInformationData(serverId,msecs));
	return si;
}

JHead JRequestServerInfo::getHead(JID id)const
{
	return JServerInfo(id).head();
}
