#include "jrequestbase.h"

#include <QCoreApplication>

#include "../global/jelapsedtimer.h"
#include "../network/jclientsocketbase.h"
#include "../global/shost.h"

const static QString error_no="no error";

/*!
	\file jrequestbase.h
	\brief 定义了 JRequestBase 类
*/

/*!
	\class JRequestBase jrequestbase.h "service/jrequestbase.h"
	\ingroup client
	\brief 向服务器发送请求的基类。

	客户端向服务器发送各种请求，需要完成各种功能。\n
	请求将数据与底层的套接字分开，对套接字进行了一定的封装。\n
	JRequestBase封装了一些各种请求都需要用到的功能。\n
*/

JRequestBase::JRequestBase(QObject *parent)
	:QObject(parent)
{
}
