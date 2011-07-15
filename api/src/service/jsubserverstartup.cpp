#include "service/jsubserverstartup.h"

#include "service/jrequestport.h"
#include "service/jrequestlogin.h"
#include "service/jsendgsinfo.h"
#include "service/jcryprorecorder.h"

JSubServerStartup::JSubServerStartup()
{
	m_ps=new JRequestPort;
	m_login=new JRequestLogin;
	m_gis=new JSendGsInfo;
}

JSubServerStartup::EReturnValue JSubServerStartup::startup()const
{
//	JPortService ps;
	EReturnValue ret=ERV_Success;
	m_ps->setServerPort(EST_FREEPORT,m_host);
	SHost loginHost=m_ps->rqsServerPort(EST_LOGIN);
	m_login->connectToHost(loginHost.m_address,loginHost.m_port);
	if(!m_login->waitForConnected(1000))
	{
		qDebug()<<"connect failed . error :"<<m_login->getConnectError();
		return ERV_ConnectFailed;
	}
	m_login->login(m_loginname,m_passwd,m_role);
	if(!m_login->waitForLogined(1000))
	{
		qDebug()<<"Login failed . error :"<<m_login->getLoginError();
		return ERV_LoginFailed;
	}
//	JGsInfoService gis;
	SHost gsiHost=m_ps->rqsServerPort(EST_SUBSERVER);
	m_gis->connectToHost(gsiHost.m_address,gsiHost.m_port);
	if(!m_gis->waitForConnected(1000))
	{
		qDebug()<<"game server connect failed . error :"
				<<m_gis->error();
		return ERV_ConnectFailed;
	}
	JCryproRecorder cr;
	m_gis->sendCrypro(cr.getUserId(),cr.getCrypro());
	if(!m_gis->waitForPassLoginHash(1000))
	{
		qDebug()<<"1 gis pass Login Hash failed . error :"
				<<m_gis->state()
				<<m_gis->error();
		return ERV_PlhFailed;
	}
//	SubServer::SGameInfo2 gi;
//	{
//		gi.m_gameId=109;
//		gi.m_name="sample game";
//		gi.m_author=901;
//		gi.m_version=JVersion(1);
//		gi.m_introduction="this is just a sample.";
//	}
	if(m_gameinfo.m_gameId>0 && !m_gameinfo.m_name.isEmpty())
	{
		m_gis->sendGameInfo(m_gameinfo);
		if(!m_gis->waitForSend(1000))
		{
			qDebug()<<"send game info failed . error :"
					<<m_gis->error();
			ret=ERV_SendFailed;
		}else{
			qDebug()<<"send game info success.";
		}
	}
//	SubServer::SSubServer ss;
//	{
//		ss.m_serverId=53379;
//		ss.m_name="sample game server";
//		ss.m_address=QHostAddress::LocalHost;
//		ss.m_port=60373;
//		ss.m_type=SubServer::SSubServer::ET_GameServer;
//	}
	m_gis->sendServerInfo(m_serverinfo);
	if(!m_gis->waitForSend(1000))
	{
		qDebug()<<"send server info failed . error :"
				<<m_gis->error();
		ret=ERV_SendFailed;
	}else{
		qDebug()<<"send server info success.";
	}
	m_gis->sendRelation(m_serverinfo.m_serverId,m_gameinfo.m_gameId,m_gameinfo.m_version);
	if(!m_gis->waitForSend(1000))
	{
		qDebug()<<"send relation failed . error :"
				<<m_gis->error();
		ret=ERV_SendFailed;
	}else{
		qDebug()<<"send relation success.";
	}
	qDebug()<<m_serverinfo.m_name<<"startup success.";
	return ret;
}
