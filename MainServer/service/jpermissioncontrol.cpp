#include "jpermissioncontrol.h"

#include <Information/JInformation>
#include <Global/Login>
#include <Global/Command>

#include "../database/jabstractdatabasefactory.h"

using namespace NetworkData;

JPermissionControl::JPermissionControl(JID userId)
	:m_userId(userId)
{
}

bool JPermissionControl::checkInformation(JID protocol,const JHead& head)
{
	JAbstractDatabaseFactory* dbFactory=JAbstractDatabaseFactory::getInstance();
	switch(protocol){
	case EIP_DownloadRemoteMtime:
		return (m_userId > 0);
		break;
	case EIP_DownloadData:
		return (m_userId > 0);
		break;
	case EIP_UploadData:
		switch(head.m_type){
		case EIT_UserInfo://只有自己和Admin可以更改用户信息
			if(head.m_id == m_userId) return true;
			{
				JAbstractLoginDB* logindb=dbFactory->createLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
			}
			return false;
			break;
		case EIT_GameInfo://只有游戏运营者才能更改游戏信息
			{
				JID gameId = head.m_id;
				JAbstractGameInfoDB* gameinfoDb=dbFactory->createGameInfoDB();
				JGameInfo gameinfo = gameinfoDb->getGameInfoById(gameId);
				return gameinfo.getRunner() == m_userId;
			}
			break;
		case EIT_ServerInfo:
			{
				JID serverId = head.m_id;
				JAbstractServerInfoDB* serverinfoDB = dbFactory->createServerInfoDB();
				JServerInfo serverinfo = serverinfoDB->getServerInfoById(serverId);
				return serverinfo.getRunner() == m_userId;
			}
		}

		break;
	default:
		return false;
	}
	return false;
}

bool JPermissionControl::checkCommand(JID type,JID)
{
	JAbstractDatabaseFactory* dbFactory=JAbstractDatabaseFactory::getInstance();
	switch(type){
	case ECT_Shutdown:
	case ECT_Restart:
		{
			JAbstractLoginDB* logindb=dbFactory->createLoginDB();
			if(logindb->checkRole(m_userId,ROLE_ROOT)) return true;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}
