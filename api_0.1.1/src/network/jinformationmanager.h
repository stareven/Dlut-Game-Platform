#ifndef JINFORMATIONMANAGER_H
#define JINFORMATIONMANAGER_H

#include "jinformation.h"

#include <QHash>

namespace NetworkData{

	/*!
		由JClientInformationProcessor负责保存收到的信息。
	*/
	class JInformationManager
	{
	JInformationManager();
	public:
		static JInformationManager& getInstance();
		const JInformation getInformation(const JHead& head)const;
		JInformation& getInformation(const JHead& head);
		JCode setRemoteMtime(const JHead& head,JTime_t time);
		JCode setLocalMtime(const JHead& head,JTime_t time);
		JCode setData(const JHead& head,const QByteArray& data);
	private:
		QHash<JHead,JInformation> m_informations;
	};
}

#endif // JINFORMATIONMANAGER_H
