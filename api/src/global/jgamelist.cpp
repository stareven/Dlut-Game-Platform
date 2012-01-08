#include "jgamelist.h"

#include <QDataStream>

using namespace NetworkData;

/*!
    \class JGameList jgamelist.h <DataStruct/JGameList>
    \ingroup global
    \brief 返回游戏的ID、名称列表
    
    这个类在设计上看起来比较怪，
    它直接继承自QMap，保存ID与游戏名称的对应关系，
    游戏ID作为键，游戏名称作为值。
    并且能够通过QMap所拥有的方法来访问这个类的数据。
*/

/*!
    \brief 构造函数
    
    以后构造函数可不可以不写了？
*/
JGameList::JGameList()
	:JSerializableData(-1)
{
}

/*!
    \brief 从二进制数据中序列化出游戏列表
*/
void JGameList::fromByteArray(const QByteArray& data)
{
	QDataStream stream(data);
	stream>>*this;
}

/*!
    \brief 将游戏列表序列化为二进制数据
*/
QByteArray JGameList::toByteArray()const
{
	QByteArray data;
	QDataStream stream(&data,QIODevice::WriteOnly);
	stream<<*this;
	return data;
}

/*!
    \brief 获得头信息
    
    \sa JSerializableData::head()
*/
JHead JGameList::head()const
{
	return JHead(-1,EIT_GameInfo,1);
}
