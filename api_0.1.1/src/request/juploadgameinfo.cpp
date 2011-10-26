#include "juploadgameinfo.h"

#include "../global/jgameinfo.h"

using namespace NetworkData;

JUploadGameInfo::JUploadGameInfo(QObject *parent) :
    JInformationSendBase(parent)
{
}

JCode JUploadGameInfo::pushGameInfo(const JGameInfo& gameinfo,int msecs)
{
	return pushInformationData(gameinfo.getGameId(),gameinfo.toByteArray(),msecs);
}

JHead JUploadGameInfo::getHead(JID id)const
{
	return JGameInfo(id).head();
}
