#include "jversion.h"

#include <QDataStream>

/*!
	\class JVersion jversion.h "global/jversion.h"
	\ingroup global
	\brief 管理版本号。
	
	一个版本号应包含四部分：<主版本号>.<次版本号>.<发布号>-<开发号>
	每一部分应该是一个不大于255的整数。因此版本号可以保存在一个\c quint32 类型中。
*/

/*!
	\brief 以\a data 构造一个版本号。
	
	默认将构造一个空版本号。
	\sa isNull()
*/
JVersion::JVersion(quint32 data)
{
	m_data=data;
}

/*!
	\brief 判断当前版本号是否为空。
	
	如果保存的数据等于0xFFFFFFFF，则为空。
*/
bool JVersion::isNull()const
{
	return m_data == 0xFFFFFFFF;
}

/*!
	如果当前版本号低于\a b ，返回true；否则返回false。
*/
bool JVersion::operator<(const JVersion& b)const
{
	return m_data < b.m_data;
}

/*!
	如果当前版本号高于\a b ，返回true；否则返回false。
*/
bool JVersion::operator>(const JVersion& b)const
{
	return m_data > b.m_data;
}

/*!
	如果当前版本号等于\a b ，返回true；否则返回false。
*/
bool JVersion::operator==(const JVersion& b)const
{
	return m_data == b.m_data;
}

/*!
	如果当前版本号不等于\a b ，返回true；否则返回false。
*/
bool JVersion::operator!=(const JVersion& b)const
{
	return m_data != b.m_data;
}

/*!
	\brief 直接获取内部保存的\c quint32 值。
*/
quint32 JVersion::getData()const
{
	return m_data;
}

/*!
	\relates JVersion
	\brief 将版本号\a ver 输出到\a stream 流中。
	
	格式：32位无符号整数。
*/
QDataStream& operator<<(QDataStream& stream,const JVersion& ver)
{
	stream<<ver.m_data;
	return stream;
}

/*!
	\relates JVersion
	\brief 从\a stream 流中读出版本号到\a ver 中。
	
	格式：32位无符号整数。
*/
QDataStream& operator>>(QDataStream& stream,JVersion& ver)
{
	stream>>ver.m_data;
	return stream;
}
