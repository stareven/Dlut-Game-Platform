#ifndef JGAMEINFO_H
#define JGAMEINFO_H

#include "jserializabledata.h"
#include "jglobal.h"
#include "jversion.h"

#include <QUrl>

class JGameInfo : public JSerializableData
{
public:
    JGameInfo();
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head(JID id)const;

	const QString& getName();
private:
	JID m_gameId;
	QString m_name;
	JVersion m_version;
	JID m_author;
	QString m_introduction;
	JID m_serverId;
	QUrl m_downloadUrl;
};

#endif // JGAMEINFO_H
