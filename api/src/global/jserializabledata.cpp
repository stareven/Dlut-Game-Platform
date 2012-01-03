#include "jserializabledata.h"

/*!
    \class JSerializableData jserializabledata.h <DataStruct/JSerializableData>
    \ingroup global
    \brief 可序列化的数据的抽象基类
    
    可序列化对象需要实现三个抽象方法：
    \li fromByteArray() 从二进制数据中序列化出对象数据
    \li toByteArray() 将对象数据序列化为二进制数据
    \li head() 对象的头信息。通过头信息索引数据。
*/
/*!
    \fn virtual void JSerializableData::fromByteArray(const QByteArray& data)=0;
    \brief 从二进制数据中序列化出对象数据
*/
/*!
    \fn virtual QByteArray JSerializableData::toByteArray()const=0;
    \brief 将对象数据序列化为二进制数据
*/
/*!
    \fn virtual NetworkData::JHead JSerializableData::head()const=0;
    \brief 返回对象的头信息。
    
    通过头信息索引数据，以进行储存与查找。
*/

/*!
    \brief 构造函数
    
    必须提供一个 \a id 值。
*/
JSerializableData::JSerializableData(JID id)
{
	m_id=id;
}

/*!
    \brief 获取id值。
*/
JID JSerializableData::getId()const
{
	return m_id;
}

/*!
    \brief 设置 \a id 
*/
void JSerializableData::setId(JID id)
{
	m_id=id;
}
