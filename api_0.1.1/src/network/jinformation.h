#ifndef JINFORMATION_H
#define JINFORMATION_H

#include <QtGlobal>
#include <QByteArray>

#include "../global/jglobal.h"

namespace NetworkData{
	class JInformation
	{
	public:
		JInformation();
	private:
		qint32 m_head;
		JTime_t m_lastModifyTime;///< 服务器端数据内容的最后修改时间
		JTime_t m_lastAccessTime;///< 最近一次请求lastModifiedTime的时间
		JTime_t m_lastReadTime;///< 本地最近一次得到数据的时间
		QByteArray m_data;
	};
}

#endif // JINFORMATION_H
