#ifndef JINFORMATION_H
#define JINFORMATION_H

#include <QtGlobal>
#include <QByteArray>

#include "../global/jglobal.h"

namespace NetworkData{
	struct JHead{
		JType m_type;
		quint8 m_meta;
		qint16 m_category;
		JID m_id;
	};
	class JInformation
	{
	public:
		JInformation();
		/// update lastModifyTime and lastAccessTime;
		JCode setLastModifyTime(JTime_t time);
		/// update data and lastReadTime
		JCode setData(const QByteArray& data);
	private:
		JHead m_head;
		JTime_t m_lastModifyTime;///< 服务器端数据内容的最后修改时间
		JTime_t m_lastAccessTime;///< 最近一次得到lastModifiedTime的时间
		JTime_t m_lastReadTime;///< 本地最近一次得到数据的时间
		QByteArray m_data;
	};
}

#endif // JINFORMATION_H
