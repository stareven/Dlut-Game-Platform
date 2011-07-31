#include "service/jlhcrequestbase.h"

#include <QCoreApplication>

#include "network/jlhcsocketbase.h"
#include "global/jelapsedtimer.h"

/*!
	\class JLhcRequestBase
	\brief 需要Login hash confirm的请求的基类。

	客户端向服务器发送的部分请求需要通过Login hash confirm。这个类是这类请求的基类，对Login hash confirm的过程提供了封装。\n
	当已经连接成功后，需要调用 sendLoginHashCode() 发送Login hash code。\n
	之后可以监听lhcResult() 信号或调用waitForLhc() 函数来获得Login hash confirm的结果。

	\sa JLoginHashCodeRecorder, JRequestBase
*/

/*!
	\fn JLhcRequestBase::lhcResult(bool result)

	这个信号是Login hash confirm的结果。\a result 表示是否通过了Login hash confirm。
*/

/*!
	JLhcRequestBase 的构造函数。
*/
JLhcRequestBase::JLhcRequestBase(QObject *parent) :
    JRequestBase(parent)
{
	m_socket=NULL;
	m_state=EPS_Init;
}

/*!
	发送Login hash code 。
	\a userId 表示当前用户的ID，\a code 表示Login hash code。\n
	如果套接字为空或已经通过Login hash confirm，函数将直接返回。\n
	调用此函数后， getLhcState() 将变为 EPS_Sending 。
*/
void JLhcRequestBase::sendLoginHashCode(JID userId,const QByteArray& code)
{
	if(m_socket==NULL)
	{
		qDebug()<<"JLhcRequestBase: socket is NULL";
		return;
	}
	if(EPS_Success==m_state)
	{
		qDebug()<<"JLhcRequestBase: already plh";
		return;
	}
	m_state=EPS_Sending;
	m_socket->sendLoginHashCode(userId,code);
}

/*!
	返回Login hash confirm的状态。
*/
JLhcRequestBase::ELhcState JLhcRequestBase::getLhcState()const
{
	return m_state;
}

/*!
	等待\a msecs 毫秒或收到Login hash confirm的结果。
	返回true ： Login hash confirm成功。
	返回false ： Login hash confirm失败或时间超过\a msecs 毫秒。
*/
bool JLhcRequestBase::waitForLhc(int msecs )const
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getLhcState()!=EPS_Sending)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return getLhcState()==EPS_Success;
}

void JLhcRequestBase::setSocket(JLhcSocketBase* socket)
{
	m_socket=socket;
	connect(m_socket,SIGNAL(rcvLoginHashConfirm(bool)),SLOT(on_socket_rcvLoginHashConfirm(bool)));
	JRequestBase::setSocket(socket);
}

void JLhcRequestBase::on_socket_rcvLoginHashConfirm(bool lhc)
{
	if(lhc)
	{
		m_state=EPS_Success;
	}else{
		m_state=EPS_Failed;
	}
	emit lhcResult(lhc);
}
