#include "jhead.h"

#include <QDataStream>

using namespace NetworkData;

/*!
    \class NetworkData::JHead jhead.h Information/JInformation
    \ingroup global
    \brief 记录 NetworkData 的头信息
    
    NetworkData 需要通过头信息索引数据内容。
*/

/*!
    \enum EInformationType
    \brief 数据的类型
*/

/*!
    \var EInformationType EIT_UserInfo
    \brief 用户信息
*/

/*!
    \var EInformationType EIT_GameInfo
    \brief 游戏信息
*/

/*!
    \var EInformationType EIT_ServerInfo
    \brief 服务器信息
*/

/*!
    \brief 构造函数
    
    头信息 \n
    \a id 信息ID 。 不同类型的信息的id的含义不相同\n
    \a type 信息类型 \n
    \a category 信息分类 \n
*/
JHead::JHead(JID id,JType type, qint16 category )
    :m_type(type),
    m_category(category),
    m_id(id)
{
}

/*!
    \brief 重载 == 运算符
    \relates NetworkData::JHead
*/
bool operator==(const JHead& a,const JHead& b)
{
    if(a.m_type != b.m_type) return false;
    if(a.m_category != b.m_category) return false;
    if(a.m_id != b.m_id) return false;
    return true;
}

/*!
    \brief 重载 qHash 函数
    \relates NetworkData::JHead
    
    为了能使用 QSet 类保存 JHead 数据，必须重载 qHash 函数。
*/
uint qHash(const JHead& head)
{
    return (((uint)head.m_type) <<16) + (uint)head.m_category + (uint)head.m_id;
}

/*!
    \brief 重载 < 运算符
    
    为了能使用 QMap 类保存 JHead 数据，必须重载 < 运行符。
*/
bool JHead::operator<(const JHead& head)const
{
    if(m_type!=head.m_type) return m_type<head.m_type;
    if(m_category!=head.m_category) return m_category<head.m_category;
    if(m_id!=head.m_id) return m_id<head.m_id;
    return false;
}

/*!
    \brief 序列化方法
    \relates NetworkData::JHead
*/
QDataStream& operator<<(QDataStream& stream,const JHead& head)
{
    stream<<head.m_type;
    stream<<head.m_category;
    stream<<head.m_id;
    return stream;
}

/*!
    \brief 反序列化方法
    \relates NetworkData::JHead
*/
QDataStream& operator>>(QDataStream& stream,JHead& head)
{
    stream>>head.m_type;
    stream>>head.m_category;
    stream>>head.m_id;
    return stream;
}
