#include "service/jrequestbase.h"

#include <QCoreApplication>

#include "network/jsocketbase.h"
#include "global/jelapsedtimer.h"

const static QString error_no="no error";

/*!
	\class JRequestBase
	\brief 向服务器发送请求的基类。

	客户端向服务器发送各种请求，需要完成各种功能。
	请求将数据与底层的套接字分开，对套接字进行了一定的封装。
	JRequestBase封装了一此各种请求都需要用到的功能。
*/

/*!
	\enum JRequestBase::EConnectState

	连接状态。

	\value ECS_Init 初始状态
	\value ECS_Connecting 已经开始连接到服务器
	\value ECS_Connected 已经成功连接到服务器
	\value ECS_Error 发生错误
*/

/*!
	\fn JRequestBase::connectResult(bool result)

	连接结果。
	\a result 表示是否连接成功。
*/

/*!
	\fn JRequestBase::error();

	发生错误。
	可以通过getConnectError()函数获取错误的具体内容。

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
	连接到地址为\a address 端口为\a port 的服务器。
	若套接字为空，则提示错误并立即返回。
	若已经连接，则立即返回。
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
	返回true ： 连接成功。
	返回false ： 连接失败或时间超过\a msecs 毫秒。
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
	以可读的形式返回连接错误。
*/
const QString& JRequestBase::getConnectError()const
{
	return *m_error;
}

void JRequestBase::setSocket(JSocketBase* socket)
{
	m_socket=socket;
	connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
	connect(m_socket,SIGNAL(SocketError(QString)),SLOT(on_socket_SocketError(QString)));
}

void JRequestBase::on_socket_SocketCode(JCode code)
{
	switch((ENet)code)
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
