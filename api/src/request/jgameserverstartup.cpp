#include "jgameserverstartup.h"

#include "jconnecthelper.h"
#include "jrequestlogin.h"
#include "juploadgameinfo.h"
#include "juploadserverinfo.h"
#include "../network/jmainclientsocket.h"
#include "../global/jcodeerror.h"

JGameServerStartup::JGameServerStartup()
{
}

JGameServerStartup::EReturnValue JGameServerStartup::startup()const
{
	EReturnValue ret=ERV_Success;
	JConnectHelper ch(JMainClientSocket::getInstance());
	ch.connectToHost(m_mainserver);
	if(!ch.waitForConnected(1000)){
		qDebug()<<"connect failed . error :"<<ch.getConnectError();
		return ERV_ConnectFailed;
	}
	JRequestLogin login;
	login.login(m_loginname,m_passwd,m_role);
	if(!login.waitForLogined(1000))
	{
		qDebug()<<"Login failed . error :"<<login.getLoginError();
		return ERV_LoginFailed;
	}
	if(m_gameinfo.getGameId()>0 && !m_gameinfo.getName().isEmpty())
	{
		JUploadGameInfo ugi;
		if(ESuccess != ugi.pushGameInfo(m_gameinfo,1000)){
			qDebug()<<"send game info failed . error :"
					<<ugi.getSendResult(m_gameinfo.getGameId());
			return ERV_SendFailed;
		}else{
			qDebug()<<"send game info success.";
		}
	}
	if(m_serverinfo.getServerId()>0 && !m_serverinfo.getHost().isNull()){
		JUploadServerInfo usi;
		if(ESuccess != usi.pushServerInfo(m_serverinfo,1000)){
			qDebug()<<"send server info failed . error :"
					<<usi.getSendResult(m_serverinfo.getServerId());
			return ERV_SendFailed;
		}else{
			qDebug()<<"send server info succeed.";
		}
	}
	qDebug()<<m_serverinfo.getName()<<"startup success.";
	return ret;
}
