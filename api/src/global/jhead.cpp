#include "jhead.h"

#include <QDataStream>

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

bool JHead::operator<(const JHead& head)const
{
    if(m_type!=head.m_type) return m_type<head.m_type;
    if(m_category!=head.m_category) return m_category<head.m_category;
    if(m_id!=head.m_id) return m_id<head.m_id;
    return false;
}

QDataStream& operator<<(QDataStream& stream,const JHead& head)
{
    stream<<head.m_type;
    stream<<head.m_category;
    stream<<head.m_id;
    return stream;
}

QDataStream& operator>>(QDataStream& stream,JHead& head)
{
    stream>>head.m_type;
    stream>>head.m_category;
    stream>>head.m_id;
    return stream;
}
