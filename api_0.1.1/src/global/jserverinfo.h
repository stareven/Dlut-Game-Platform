#ifndef JSERVERINFO_H
#define JSERVERINFO_H

#include <QString>

#include "jserializabledata.h"
#include "jglobal.h"
#include "shost.h"

class JServerInfo : public JSerializableData
{
public:
    JServerInfo();
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head(JID id)const;

	const QString& getName()const;
private:
	JID m_serverId;
	QString m_name;
	SHost m_host;
};

#endif // JSERVERINFO_H
