#ifndef JGLOBAL_H
#define JGLOBAL_H

#include <QtGlobal>

/*!
	\file jglobal.h
	\ingroup global
	\brief 整个项目都需要用到的一些定义。
*/

/*!
	\brief 整个项目通用的一个ID类型。
	
	整个项目中有很多地方需要用到ID，比如用户ID，服务器ID，游戏ID等。\n
	在此统一将所有的ID定义为32位有符号整数。\n
*/
typedef qint32 JID;

/*!
	\brief 整个项目通用的函数返回值类型。
	
	一些函数的返回值代表函数是否执行成功。\n
	0代表成功，其它的代表各种错误。\n
*/
typedef qint16 JCode;

/*!
	\brief 网络状态。

	\warning 这个值将会被取消。
*/
enum ENet{
    EN_CONNECTED,
    EN_DISCONNECTED
};

/*!
	\defgroup global globalapi
	\brief 整个项目需要用到的一些数据定义等。
*/

#endif // JGLOBAL_H
