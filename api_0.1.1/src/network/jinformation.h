#ifndef JINFORMATION_H
#define JINFORMATION_H

#include <QtGlobal>
#include <QByteArray>

#include "../global/jglobal.h"

namespace NetworkData{
	struct JHead;
}
bool operator==(const NetworkData::JHead&,const NetworkData::JHead&);
uint qHash(const NetworkData::JHead&);

namespace NetworkData{
	struct JHead{
		JType m_type;
		qint16 m_category;
		JID m_id;

		JHead(JID id=-1,JType type=-1,qint16 category=-1);
		friend bool ::operator==(const JHead&,const JHead&);
		friend uint ::qHash(const JHead&);
		bool operator<(const JHead& head)const;
	};
	enum EInformationType{
		EIT_UserInfo,
		EIT_GameInfo,
		EIT_ServerInfo,
	};
	enum EInformationProtocol{
		EIP_RemoteMtime,
		EIP_Data,
		EIP_Max,
	};

	class JInformation
	{
	public:
		JInformation(const JHead& head=JHead(-1));
		/// update m_remoteMtime
		JCode setRemoteMtime(JTime_t time);
		/// update m_localMtime
		JCode setLocalMtime(JTime_t time);
		/// update data
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

class QDataStream;
QDataStream& operator<<(QDataStream&,const NetworkData::JHead&);
QDataStream& operator>>(QDataStream&,NetworkData::JHead&);

#endif // JINFORMATION_H
