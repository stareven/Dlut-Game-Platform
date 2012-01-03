#include "jconnecthelper.h"

#include <QCoreApplication>

#include "../global/jelapsedtimer.h"
#include "../network/jclientsocketbase.h"
#include "../global/shost.h"

const static QString error_no="no error";

/*!
	\fn JConnectHelper::error();
	\brief 发生错误。

	可以通过getConnectError()函数以可读的字符串获取错误的具体内容。

	\sa getConnectError()
*/

/*!
	构造函数。
*/
JConnectHelper::JConnectHelper(JClientSocketBase* socket,QObject *parent) :
	QObject(parent)
{
	m_error=error_no;
	m_socket=socket;
	connect(m_socket,
			SIGNAL(error(JCode)),
			SLOT(on_socket_SocketError(JCode)));
}

/*!
	连接到地址为\a host 服务器。\n
	若套接字为空，则发射 error() 信号、从 QDebug 输出错误提示并立即返回。\n
	若已经连接，则从 QDebug 输出错误提示并立即返回。\n
	调用此函数后， getConnectState() 将变为 ECS_Connecting 。
*/
void JConnectHelper::connectToHost(const SHost& host)
{
	if(m_socket==NULL)
	{
		qDebug()<<"JRequestBase: socket is NULL";
		const static QString error_socket_null="socket is NULL";
		m_error=error_socket_null;
		emit error();
		return;
	}
	if(m_socket->socketState()==QAbstractSocket::ConnectedState)
	{
		qDebug()<<"JRequestBase::connectToHost : already connected.";
		return;
	}
	m_socket->connectToServer(host);
}

/*!
	等待\a msecs 毫秒或收到连接结果。
	\retval true 连接成功。
	\retval false 连接失败或时间超过\a msecs 毫秒。
*/
bool JConnectHelper::waitForConnected(int msecs)const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(m_socket->socketState()!=QAbstractSocket::ConnectingState)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_socket->socketState()==QAbstractSocket::ConnectedState;
}

/*!
	以可读的字符串返回连接错误。
*/
const QString& JConnectHelper::getConnectError()const
{
	return m_error;
}

void JConnectHelper::on_socket_SocketError(JCode errorCode)
{
	m_error=tr("network error : %1").arg(errorCode);
	emit error();
}
