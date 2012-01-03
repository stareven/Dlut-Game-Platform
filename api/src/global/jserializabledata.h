#ifndef JSERIALIZABLEDATA_H
#define JSERIALIZABLEDATA_H

#include <QByteArray>

#include "../global/jhead.h"

/*!
    \file jserializabledata.h
    \ingroup global
    \brief 定义了 JSerializableData 接口
*/

class JSerializableData
{
public:
	JSerializableData(JID id);
	virtual void fromByteArray(const QByteArray& data)=0;
	virtual QByteArray toByteArray()const=0;
	virtual NetworkData::JHead head()const=0;
private:
	JID m_id;
protected:
	JID getId()const;
	void setId(JID id);
};

#endif // JSERIALIZABLEDATA_H
