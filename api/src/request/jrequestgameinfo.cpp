#include "jrequestgameinfo.h"

using namespace NetworkData;

JRequestGameInfo::JRequestGameInfo(QObject *parent) :
    JInformationRequestBase(parent)
{
}

JGameInfo JRequestGameInfo::pullGameInfo(JID gameId,int msecs)
{
	JGameInfo gi(gameId);
	gi.fromByteArray(pullInformationDataById(gameId,msecs));
	return gi;
}

JGameList JRequestGameInfo::pullGameList(int msecs)
{
	JGameList gl;
	gl.fromByteArray(pullInformationData(gl.head(),msecs));
	return gl;
}


NetworkData::JHead JRequestGameInfo::getHeadById(JID id) const
{
	return JGameInfo(id).head();
}
