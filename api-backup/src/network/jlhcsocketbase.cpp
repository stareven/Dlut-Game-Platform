#include "network/jlhcsocketbase.h"

#include <QDataStream>

/*!
	\file jlhcsocketbase.h
	\brief 定义了 JLhcSocketBase 类
*/

/*!
	\class JLhcSocketBase jlhcsocketbase.h "network/jlhcsocketbase.h"
	\ingroup client
	\brief 封装需要\ref LoginHashConfirm 的通信
	
	服务器端的部分通信需要确认身份。\n
	确认身份的方式是通过\ref LoginHashConfirm 。\n
	
	\section lhc_protocol 通信协议
	首先，这个通信协议只定义了\ref base_protocol "基本通信协议" 中data的部分。\n
	查看完整的通信协议，请见\ref base_protocol "基本通信协议" 。\n
	这是一个有状态的连接。也就是说，在通过\ref LoginHashConfirm 之前和之后的通信协议并不相同。
	- 之前 ：
	  - 客户端向服务器端 : <JID:userId> <QByteArray:code>
	    -# ::JID 类型，表示客户端用户ID。
	    -# QByteArray 类型，以Qt QDataStream 的方式序列化为数据流，表示\ref LoginHashCode。
	  - 服务器端向客户端 ：<bool:result>
	    -# 表示\ref LoginHashConfirm 的结果。
	- 之后 ： 由子类定义。
	
	关于Qt QDataStream 的序列化格式，请参见Qt文档<a href="http://doc.qt.nokia.com/4.7/datastreamformat.html" target="_blank">Serializing Qt Data Types</a>
	
	\sa afterLhc()
*/

/*!
	\fn JLhcSocketBase::rcvLoginHashConfirm(bool lhc)
	\brief 收到\ref LoginHashConfirm 的结果
	
	\a lhc 表示是否通过\ref LoginHashConfirm
*/

/*!
	\fn JLhcSocketBase::afterLhc(const QByteArray&)
	\brief 在通过\ref LoginHashConfirm 后，由这个函数处理数据
	
	子类需要重写这个函数来处理通过\ref LoginHashConfirm 后的数据。
*/

/*!
	\brief 构造函数
*/
JLhcSocketBase::JLhcSocketBase(QObject *parent) :
    JSocketBase(parent)
{
	m_lhc=false;
}

/*!
	\brief 发送\ref LoginHashCode
	
	若已经通过\ref LoginHashConfirm ，这个函数会发射 rcvLoginHashConfirm() 信息后立即返回，\n
	而不会向服务器发送\ref LoginHashCode 。
*/
void JLhcSocketBase::sendLoginHashCode(JID id,const QByteArray& code)
{
	if(m_lhc){
		emit rcvLoginHashConfirm(m_lhc);
		return;
	}
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<id;
	outstream<<code;
	sendData(outdata);
}

/*!
	\brief 数据处理函数
	
	在通过\ref LoginHashConfirm
	  - 之前，由这个函数处理数据。\n
	  如果收到\ref LoginHashConfirm 的结果，这个函数会发射 rcvLoginHashConfirm() 信号
	  - 之后，交由 afterLhc() 函数处理数据。
*/
void JLhcSocketBase::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	if(m_lhc)
	{
		afterLhc(data);
	}else{
		stream>>m_lhc;
		emit rcvLoginHashConfirm(m_lhc);
	}
}
