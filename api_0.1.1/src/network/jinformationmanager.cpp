#include "jinformationmanager.h"

using namespace NetworkData;

JInformationManager::JInformationManager()
{
}

JInformationManager& JInformationManager::getInstance()
{
	static JInformationManager instance;
	return instance;
}

const JInformation JInformationManager::getInformation(const JHead& head)const
{
	return m_informations.value(head,JInformation(head));
}

JInformation& JInformationManager::getInformation(const JHead& head)
{
	if(!m_informations.contains(head)){
		m_informations.insert(head,JInformation(head));
	}
	return m_informations[head];
}

JCode JInformationManager::setRemoteMtime(const JHead& head,JTime_t time)
{
	return getInformation(head).setRemoteMtime(time);
}

JCode JInformationManager::setLocalMtime(const JHead& head,JTime_t time)
{
	return getInformation(head).setLocalMtime(time);
}

JCode JInformationManager::setData(const JHead& head,const QByteArray& data)
{
	return getInformation(head).setData(data);
}
