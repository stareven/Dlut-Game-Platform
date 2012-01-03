#include "jinformation.h"

using namespace NetworkData;

JInformation::JInformation(const JHead& head)
	:m_head(head)
{
	m_remoteMtime=0;
	m_localMtime=0;
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
