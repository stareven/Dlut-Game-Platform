#ifndef JSERVERINFO_H
#define JSERVERINFO_H

#include <QString>

#include "jserializabledata.h"
#include "jglobal.h"
#include "shost.h"

class JServerInfo : public JSerializableData
{
public:
	JServerInfo(JID serverId=-1);
	JServerInfo(JID serverId,
				const QString& name,
				JID runner,
				const SHost& host);
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head()const;

	JID getServerId()const;
	const QString& getName()const;
	JID getRunner()const;
	const SHost& getHost()const;
private:
	QString m_name;
	JID m_runner;
	SHost m_host;
};

#endif // JSERVERINFO_H
