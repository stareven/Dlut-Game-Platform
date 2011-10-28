#include "service/jsendgsinfo.h"

#include <QCoreApplication>

#include "network/jsendgsinfosocket.h"
#include "global/jelapsedtimer.h"

/*!
	\file jsendgsinfo.h
	\brief 定义了 JSendGsInfo 类
*/

/**
	\class JSendGsInfo jsendgsinfo.h "service/jsendgsinfo.h"
	\ingroup subserver
	\brief SubServer向MainServer发送相关信息。

	SubServer启动后，需要向MainServer发送：
	  -# SubServer相关信息。\n
	  -# 游戏相关信息。\n
	  -# SubServer与游戏的关联。
	  .
	请求的过程：
	  -# 通过 JRequestPort 获得用户信息服务的端口。\n
	  -# 调用 connectToHost() 函数连接服务器。\n
	  -# 调用 sendLoginHashCode() 函数发送Login hash code。\n
	  -# 调用 send***() 发送相关信息。\n
	  .
*/

/*!
	\brief 构造函数
*/
JSendGsInfo::JSendGsInfo(QObject *parent) :
	JLhcRequestBase(parent)
{
	m_state=ESS_Init;
    m_socket=new JSendGsInfoSocket(this);
	m_error=0;
	setSocket(m_socket);
	connect(m_socket,SIGNAL(rcvSendCode(JID,JCode)),SLOT(on_socket_rcvSendCode(JID,JCode)));
}

/**
	\brief 发送SubServer相关信息。
	
	\sa SubServer::SSubServer
*/
void JSendGsInfo::sendServerInfo(const SubServer::SSubServer& ss)
{
	m_state=ESS_Sending;
	m_socket->sendServerInfo (ss);
}

/**
	\brief 发送游戏相关信息。
	
	\sa SubServer::SGameInfo2
*/
void JSendGsInfo::sendGameInfo(const SubServer::SGameInfo2& gi)
{
	m_state=ESS_Sending;
	m_socket->sendGameInfo (gi);
}

/**
	\brief 发送SubServer与游戏的关联。
	表示\a serverId 是\a gameId 对应的SubServer。
*/
void JSendGsInfo::sendRelation(JID serverId,
								  JID gameId,
								  const JVersion& gameVersion)
{
	m_state=ESS_Sending;
	m_socket->sendRelation(serverId,gameId,gameVersion);
}

/**
	\brief 获取发送状态。
	
	\sa ESgiState
*/
JSendGsInfo::ESgiState JSendGsInfo::sendGsInfoState()const
{
    return m_state;
}

/**
	\brief等待\a msecs 毫秒或收到登录结果。
	
	\retval true 登录成功。
	\retval false 登录失败或时间超过\a msecs 毫秒。
*/
bool JSendGsInfo::waitForSend(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
		if(sendGsInfoState()!=ESS_Sending)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
	return sendGsInfoState()==ESS_SendSuccess;
}

/**
	\brief 以可读的文本返回发送错误。
*/
const QString& JSendGsInfo::sendGsInfoError()const
{
    static const QString errors[]={
        tr("no error"),//0
        tr("socket can not write"),//1
        tr("socket disconnected"),//2
        tr("pass login hash failed"),//3
		tr("send failed"),//4
    };
    return errors[m_error];
}

void JSendGsInfo::on_socket_rcvSendCode(JID protocol,JCode code)
{
	qDebug()<<"JSendGsInfo::on_socket_rcvSendCode . protocol="
			<<protocol
			<<"code="
			<<code;
	if(0==code)
	{
		m_state=ESS_SendSuccess;
		m_error=0;
	}else{
		m_state=ESS_Error;
		m_error=4;
	}
}
