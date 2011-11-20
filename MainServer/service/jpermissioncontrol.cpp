#include "jpermissioncontrol.h"

#include <Information/JInformation>
#include <Global/Login>
#include <Global/Command>

#include "../database/jabstractdatabasefactory.h"

using namespace NetworkData;

JPermissionControl::JPermissionControl(JID userId)
	:m_userId(userId)
{
	m_dbFactory=JAbstractDatabaseFactory::getInstance();
}

bool JPermissionControl::checkInformation(JID protocol,const JHead& head)
{
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
				JAbstractLoginDB* logindb=m_dbFactory->createLoginDB();
				if(logindb->checkRole(m_userId,ROLE_ADMIN)) return true;
			}
			return false;
			break;
		case EIT_GameInfo://只有游戏运营者才能更改游戏信息
			{
				JID gameId = head.m_id;
				JAbstractGameInfoDB* gameinfoDb=m_dbFactory->createGameInfoDB();
				JGameInfo gameinfo = gameinfoDb->getGameInfoById(gameId);
				return gameinfo.getRunner() == m_userId;
			}
			break;
		case EIT_ServerInfo:
			{
				JID serverId = head.m_id;
				JAbstractServerInfoDB* serverinfoDB = m_dbFactory->createServerInfoDB();
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
	switch(type){
	case ECT_Shutdown:
	case ECT_Restart:
		{
			JAbstractLoginDB* logindb=m_dbFactory->createLoginDB();
			if(logindb->checkRole(m_userId,ROLE_ROOT)) return true;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

bool JPermissionControl::checkControlRole(JID,ERole targetRole,EControlRoleAction)
{
	JAbstractLoginDB* logindb=m_dbFactory->createLoginDB();
	JID testRole;
	for(testRole = targetRole+1;testRole <= ROLE_ROOT;++testRole){
		if(logindb->checkRole(m_userId,testRole)){
			return true;
		}
	}
	return false;
}

bool JPermissionControl::isMultiLoginAble(ERole role)
{
	return role == ROLE_GAMESERVERRUNNER;
}
