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
    m_error=error_no;
}

/*!
	连接到地址为\a address 端口为\a port 的服务器。\n
	若套接字为空，则发射 error() 信号、从 QDebug 输出错误提示并立即返回。\n
	若已经连接，则从 QDebug 输出错误提示并立即返回。\n
	调用此函数后， getConnectState() 将变为 ECS_Connecting 。
*/
void JRequestBase::connectToHost(const QHostAddress& address,quint16 port)
{
    if(JClientSocketBase::getInstance()==NULL)
	{
        qDebug()<<"JRequestBase: socket is NULL";
		const static QString error_socket_null="socket is NULL";
        m_error=error_socket_null;
		emit error();
		return;
	}
    if(JClientSocketBase::getInstance()->socketState()==QAbstractSocket::ConnectedState)
	{
		qDebug()<<"JRequestBase::connectToHost : already connected.";
		return;
    }
    JClientSocketBase::getInstance()->connectToServer(SHost(address,port));
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
        if(JClientSocketBase::getInstance()->socketState()!=QAbstractSocket::ConnectingState)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
    return JClientSocketBase::getInstance()->socketState()==QAbstractSocket::ConnectedState;
}

/*!
	以可读的字符串返回连接错误。
*/
const QString& JRequestBase::getConnectError()const
{
    return m_error;
}

void JRequestBase::on_socket_SocketError(const QString& socketError)
{
    m_error=socketError;
	emit error();
}
