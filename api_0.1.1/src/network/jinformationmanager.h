#ifndef JINFORMATIONMANAGER_H
#define JINFORMATIONMANAGER_H

#include "jinformation.h"

namespace NetworkData{
	class JInformationManager
	{
	JInformationManager();
	public:
		JInformation getInformation(const JHead& head);
		JCode setLastModifyTime(const JHead& head, JTime_t time);
		JCode setData(const JHead& head,const QByteArray& data);
	};
}

#endif // JINFORMATIONMANAGER_H
