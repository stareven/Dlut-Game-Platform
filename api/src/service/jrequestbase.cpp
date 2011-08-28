#include "service/jrequestbase.h"

#include <QCoreApplication>

#include "network/jsocketbase.h"
#include "global/jelapsedtimer.h"

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

/*!
	\fn JRequestBase::connectResult(bool result)
	\brief 连接结果。
	\a result 表示是否连接成功。
*/

/*!
	\fn JRequestBase::error();
	\brief 发生错误。

	可以通过getConnectError()函数以可读的字符串获取错误的具体内容。

	\sa getConnectError()
*/

/*!
	构造函数。
*/
JRequestBase::JRequestBase(QObject *parent)
	:QObject(parent)
{
	m_socket=NULL;
	m_state=ECS_Init;
	m_error=&error_no;
}

/*!
	连接到地址为\a address 端口为\a port 的服务器。\n
	若套接字为空，则发射 error() 信号、从 QDebug 输出错误提示并立即返回。\n
	若已经连接，则从 QDebug 输出错误提示并立即返回。\n
	调用此函数后， getConnectState() 将变为 ECS_Connecting 。
*/
void JRequestBase::connectToHost(const QHostAddress& address,quint16 port)
{
	if(m_socket==NULL)
	{
		qDebug()<<"JRequestBase: socket is NULL";
		m_state=ECS_Error;
		const static QString error_socket_null="socket is NULL";
		m_error=&error_socket_null;
		emit error();
		return;
	}
	if(m_state==ECS_Connected)
	{
		qDebug()<<"JRequestBase::connectToHost : already connected.";
		return;
	}
	m_state=ECS_Connecting;
	m_socket->connectToHost(address,port);
}

/*!
	获取当前的连接状态。

	\sa EConnectState
*/
JRequestBase::EConnectState JRequestBase::getConnectState()const
{
	return m_state;
}

/*!
	等待\a msecs 毫秒或收到连接结果。
	\retval true 连接成功。
	\retval false 连接失败或时间超过\a msecs 毫秒。
*/
bool JRequestBase::waitForConnected(int msecs)const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getConnectState()!=ECS_Connecting)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getConnectState()==ECS_Connected;
}

/*!
	以可读的字符串返回连接错误。
*/
const QString& JRequestBase::getConnectError()const
{
	return *m_error;
}

void JRequestBase::setSocket(JSocketBase* socket)
{
	m_socket=socket;
	connect(m_socket,SIGNAL(SocketCode(ENet)),SLOT(on_socket_SocketCode(ENet)));
	connect(m_socket,SIGNAL(SocketError(QString)),SLOT(on_socket_SocketError(QString)));
}

void JRequestBase::on_socket_SocketCode(ENet netcode)
{
	switch(netcode)
	{
	case EN_CONNECTED:
		m_state=ECS_Connected;
		m_error=&error_no;
		emit connectResult(true);
		break;
	case EN_DISCONNECTED:
		m_state=ECS_Error;
		{
			const static QString error_disconnected="disconnected";
			m_error=&error_disconnected;
		}
		emit connectResult(false);
		emit error();
		break;
	}
}

void JRequestBase::on_socket_SocketError(const QString& socketError)
{
	static QString saveError;
	saveError=socketError;
	m_state=ECS_Error;
	m_error=&saveError;
	emit connectResult(false);
	emit error();
}
