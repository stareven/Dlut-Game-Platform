#include "jinformation.h"

using namespace NetworkData;

JHead::JHead(JID id,JType type, quint8 meta, qint16 category )
	:m_type(type),
	m_meta(meta),
	m_category(category),
	m_id(id)
{
}

JInformation::JInformation(const JHead& head)
	:m_head(head)
{
}
