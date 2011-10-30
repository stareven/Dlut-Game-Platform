#ifndef JGAMEINFO_H
#define JGAMEINFO_H

#include "jserializabledata.h"
#include "jglobal.h"
#include "jversion.h"

#include <QUrl>

class JGameInfo : public JSerializableData
{
public:
	JGameInfo(JID gameId=-1);
	JGameInfo(JID gameId,
			  const QString& name,
			  const JVersion& version,
			  JID author,
			  const QString& introduction,
			  JID serverId,
			  const QUrl& downloadUrl);
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;

	JID getGameId()const;
	const QString& getName()const;
	const JVersion& getVersion()const;
	JID getAuthor()const;
	const QString& getIntroduction()const;
	JID getServerId()const;
	const QUrl& getDownloadUrl()const;
private:
	QString m_name;
	JVersion m_version;
	JID m_author;
	QString m_introduction;
	JID m_serverId;
	QUrl m_downloadUrl;
};

#endif // JGAMEINFO_H
