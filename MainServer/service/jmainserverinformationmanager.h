#ifndef JMAINSERVERINFORMATIONMANAGER_H
#define JMAINSERVERINFORMATIONMANAGER_H

#include <QByteArray>
#include <QMap>

#include <Global/Global>
#include <Information/JInformation>

class JMainServerInformationManager
{
	JMainServerInformationManager();
public:
	static JMainServerInformationManager& getInstance();
	JTime_t getMtime(const NetworkData::JHead& head);
	JTime_t getCurrentTime()const;
	QByteArray getData(const NetworkData::JHead& head)const;

	JCode updateData(const NetworkData::JHead& head,const QByteArray& data,JTime_t Mtime);
	JCode updateData(const NetworkData::JHead& head,const QByteArray& data);
private:
	QMap<NetworkData::JHead,JTime_t> m_mtime;
};

#endif // JMAINSERVERINFORMATIONMANAGER_H
