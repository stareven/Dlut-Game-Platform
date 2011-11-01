#include "jmainserverinformationmanager.h"

#include <QDateTime>

#include "database/jabstractdatabasefactory.h"

using namespace NetworkData;

JMainServerInformationManager::JMainServerInformationManager()
{
}

JMainServerInformationManager& JMainServerInformationManager::getInstance()
{
	static JMainServerInformationManager instance;
	return instance;
}

JTime_t JMainServerInformationManager::getMtime(const JHead& head)
{
	if(m_mtime.contains(head)){
		return m_mtime.value(head);
	}else{
		m_mtime.insert(head,getCurrentTime());
		return getCurrentTime();
	}
}

JTime_t JMainServerInformationManager::getCurrentTime()const
{
	return QDateTime::currentDateTime ().toTime_t();
}

QByteArray JMainServerInformationManager::getData(const JHead& head)const
{
	JSerializableData *pData=NULL;
	JAbstractDatabaseFactory* databaseFactory=JAbstractDatabaseFactory::getInstance();
	switch(head.m_type){
	case EIT_UserInfo:
		switch(head.m_category){
		case 0:
			pData=new JUserInfo(databaseFactory->createUserInfoDB()->getUserInfoById(head.m_id));
			break;
		default:
			qDebug()<<"JMainServerInformationManager::getData : no such category "<<head.m_category<<" of type "<<head.m_type;
		}
		break;
	case EIT_GameInfo:
		switch(head.m_category){
		case 0:
			pData=new JGameInfo(databaseFactory->createGameInfoDB()->getGameInfoById(head.m_id));
			break;
		case 1:
			pData = new JGameList(databaseFactory->createGameInfoDB()->getGameList());
			break;
		default:
			qDebug()<<"JMainServerInformationManager::getData : no such category "<<head.m_category<<" of type "<<head.m_type;
		}
		break;
	case EIT_ServerInfo:
		switch(head.m_category){
		case 0:
			pData=new JServerInfo(databaseFactory->createServerInfoDB()->getServerInfoById(head.m_id));
			break;
		default:
			qDebug()<<"JMainServerInformationManager::getData : no such category "<<head.m_category<<" of type "<<head.m_type;
		}
		break;
	default:
		qDebug()<<"JMainServerInformationManager::getData : no such type"<<head.m_type;
	}
	if(pData != NULL){
		return pData->toByteArray();
	}else{
		return QByteArray();
	}
}

/*!
	\retval 0 success
	\retval 0x10 bad head
	\retval 0x11 no such type
	\retval 0x12 no such category
*/
JCode JMainServerInformationManager::updateData(const JHead& head,const QByteArray& data,JTime_t Mtime)
{
	enum ERetval{ ER_Success=0,ER_BadHead=0x10,ER_NoSuchType,ER_NoSuchCategory};
	JAbstractDatabaseFactory* databaseFactory=JAbstractDatabaseFactory::getInstance();
	switch(head.m_type){
	case EIT_UserInfo:
		switch(head.m_category){
		case 0:
			{
				JUserInfo userinfo;
				userinfo.fromByteArray(data);
				databaseFactory->createUserInfoDB()->updateUserInfo(userinfo);
			}
			break;
		default:
			qDebug()<<"JMainServerInformationManager::updateData : no such category "<<head.m_category<<" of type "<<head.m_type;
			return ER_NoSuchCategory;
		}
		break;
	case EIT_GameInfo:
		switch(head.m_category){
		case 0:
			{
				JGameInfo gameinfo;
				gameinfo.fromByteArray(data);
				databaseFactory->createGameInfoDB()->updateGameInfo(gameinfo);
			}
			break;
		default:
			qDebug()<<"JMainServerInformationManager::updateData : no such category "<<head.m_category<<" of type "<<head.m_type;
			return ER_NoSuchCategory;
		}
		break;
	case EIT_ServerInfo:
		switch(head.m_category){
		case 0:
			{
				JServerInfo serverinfo;
				serverinfo.fromByteArray(data);
				databaseFactory->createServerInfoDB()->updateServerInfo(serverinfo);
			}
			break;
		default:
			qDebug()<<"JMainServerInformationManager::updateData : no such category "<<head.m_category<<" of type "<<head.m_type;
			return ER_NoSuchCategory;
		}
		break;
	default:
		qDebug()<<"JMainServerInformationManager::updateData : no such type"<<head.m_type;
		return ER_NoSuchType;
		break;
	}
	m_mtime[head]=Mtime;
	return ER_Success;
}

JCode JMainServerInformationManager::updateData(const JHead& head,const QByteArray& data)
{
	return updateData(head,data,getCurrentTime());
}
