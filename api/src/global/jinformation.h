#ifndef JINFORMATION_H
#define JINFORMATION_H

#include <QByteArray>

#include "jglobal.h"
#include "jhead.h"

/*!
    \file jinformation.h
    \ingroup global
    \brief 定义了 NetworkData::JInformation 类
*/

namespace NetworkData{
	enum EInformationProtocol{
		EIP_DownloadRemoteMtime,
		EIP_DownloadData,
		EIP_UploadData,
		EIP_Max,
	};

	class JInformation
	{
	public:
		JInformation(const JHead& head=JHead(-1));
		JCode setRemoteMtime(JTime_t time);
		JCode setLocalMtime(JTime_t time);
		JCode setData(const QByteArray& data);

		JTime_t getRemoteMtime()const;
		JTime_t getLocalMtime()const;
		const QByteArray& getData()const;
	private:
		JHead m_head;
		JTime_t m_remoteMtime;///< 服务器端数据内容的最后修改时间
		JTime_t m_localMtime;///< 本地数据内容的最后修改时间
		QByteArray m_data;
	};
}

#endif // JINFORMATION_H
