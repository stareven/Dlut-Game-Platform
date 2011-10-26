#include "jrequestgameinfo.h"

JRequestGameInfo::JRequestGameInfo(QObject *parent) :
    JInformationRequestBase(parent)
{
}

JGameInfo JRequestGameInfo::pullGameInfo(JID gameId,int msecs)
{
	JGameInfo gi(gameId);
	gi.fromByteArray(pullInformationData(gameId,msecs));
	return gi;
}

NetworkData::JHead JRequestGameInfo::getHead(JID id) const
{
	return JGameInfo(id).head();
}
