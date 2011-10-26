#include "jserializabledata.h"

JSerializableData::JSerializableData(JID id)
{
	m_id=id;
}

JID JSerializableData::getId()const
{
	return m_id;
}

void JSerializableData::setId(JID id)
{
	m_id=id;
}
