#include "jversion.h"

#include <QDataStream>

JVersion::JVersion()
{
	m_data=-1;
}

JVersion::JVersion(qint32 data)
{
	m_data=data;
}

bool JVersion::operator<(const JVersion& b)const
{
	return m_data<b.m_data;
}

qint32 JVersion::getData()const
{
	return m_data;
}

QDataStream& operator<<(QDataStream& stream,const JVersion& ver)
{
	stream<<ver.m_data;
	return stream;
}

QDataStream& operator>>(QDataStream& stream,JVersion& ver)
{
	stream>>ver.m_data;
	return stream;
}
