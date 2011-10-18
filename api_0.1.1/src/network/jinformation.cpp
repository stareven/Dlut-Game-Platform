#include "jinformation.h"

using namespace NetworkData;

JHead::JHead(JID id,JType type, qint16 category )
	:m_type(type),
	m_category(category),
	m_id(id)
{
}

bool operator==(const JHead& a,const JHead& b)
{
	if(a.m_type != b.m_type) return false;
	if(a.m_category != b.m_category) return false;
	if(a.m_id != b.m_id) return false;
	return true;
}

uint qHash(const JHead& head)
{
	return (((uint)head.m_type) <<16) + (uint)head.m_category + (uint)head.m_id;
}

JInformation::JInformation(const JHead& head)
	:m_head(head)
{
}

JCode JInformation::setRemoteMtime(JTime_t time)
{
	m_remoteMtime = time;
	return 0;
}

JCode JInformation::setLocalMtime(JTime_t time)
{
	m_localMtime = time;
	return 0;
}

JCode JInformation::setData(const QByteArray& data)
{
	m_data = data;
	return 0;
}

JTime_t JInformation::getRemoteMtime()const
{
	return m_remoteMtime;
}

JTime_t JInformation::getLocalMtime()const
{
	return m_localMtime;
}

const QByteArray& JInformation::getData()const
{
	return m_data;
}
