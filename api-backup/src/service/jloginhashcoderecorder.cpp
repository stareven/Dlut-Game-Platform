#include "service/jloginhashcoderecorder.h"

QByteArray JLoginHashCodeRecorder::s_code;
JID JLoginHashCodeRecorder::s_userId;

/*!
	\file jloginhashcoderecorder.h
	\brief 定义了 JLoginHashCodeRecorder 类
*/

/*!
	\class JLoginHashCodeRecorder jloginhashcoderecorder.h "service/jloginhashcoderecorder.h"
	\ingroup client
	\brief 管理登录用户ID及Login hash code。
	
	\section LoginHashCode Login hash code
	用户登录时，首先客户端向服务器发送用户名和密码，然后服务器对用户名和密码进行验证。\n
	验证通过后，服务端会依据某种规则产生一个Login hash code，并将用户的ID与这个Login hash code发送给客户端。\n
	
	\section LoginHashConfirm Login hash confirm
	在客户端向服务器请求端口信息、用户信息等服务时，需提供用户ID和Login hash code。\n
	服务器端会首先对用户ID与Login hash code进行验证。验证通过后服务器端才会向客户端提供各种服务，否则立即断开连接。\n
	这个过程被称作Login hash confirm。
*/

/*!
	保存Login hash \a code 及用户ID\a userId 。
*/
void JLoginHashCodeRecorder::set(const QByteArray& code,JID userId)
{
    setCode(code);
    setUserId(userId);
}

/*!
	保存Login hash \a code 。
*/
void JLoginHashCodeRecorder::setCode(const QByteArray& code)
{
    s_code=code;
}

/*!
	保存用户ID \a userId 。
*/
void JLoginHashCodeRecorder::setUserId(JID userId)
{
    s_userId=userId;
}

/*!
	获取保存的Login hash code。
*/
const QByteArray& JLoginHashCodeRecorder::getCode()const
{
    return s_code;
}

/*!
	获取保存的用户ID。
*/
JID JLoginHashCodeRecorder::getUserId()const
{
    return s_userId;
}
