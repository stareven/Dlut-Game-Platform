#ifndef JSERIALIZABLEDATA_H
#define JSERIALIZABLEDATA_H

#include <QByteArray>

#include "../network/jinformation.h"

class JSerializableData
{
public:
	virtual void fromByteArray(const QByteArray& data)=0;
	virtual QByteArray toByteArray()const=0;
	virtual NetworkData::JHead head(JID id)const=0;
};

#endif // JSERIALIZABLEDATA_H
