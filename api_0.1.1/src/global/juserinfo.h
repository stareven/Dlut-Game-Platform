#ifndef JUSERINFO_H
#define JUSERINFO_H

#include <QString>

#include "jserializabledata.h"
#include "jglobal.h"

class JUserInfo : public JSerializableData{
public:
	JUserInfo(JID id=-1,
		  const QString& name=QString(),
		  const QString& org=QString());
	void fromByteArray(const QByteArray& data);
	QByteArray toByteArray()const;
	NetworkData::JHead head(JID id)const;
private:
    JID m_userId;
	QString m_nickname;
	QString m_organization;
};

#endif // JUSERINFO_H

