#include "service/jsubserverstartup.h"

#include "service/jrequestport.h"
#include "service/jrequestlogin.h"
#include "service/jsendgsinfo.h"
#include "service/jloginhashcoderecorder.h"

/*!
	\file jsubserverstartup.h
	\brief 定义了 JSubServerStartup 类
*/

/**
	\class JSubServerStartup jsubserverstartup.h "service/jsubserverstartup.h"
	\ingroup subserver
	\brief 对SubServer的整个登录过程的封装。

	\sa startup()
*/

JSubServerStartup::JSubServerStartup()
{
	m_ps=new JRequestPort;
	m_login=new JRequestLogin;
	m_gis=new JSendGsInfo;
}

JSubServerStartup::~JSubServerStartup()
{
	delete m_ps;
	m_ps=NULL;
	delete m_login;
	m_login=NULL;
	delete m_gis;
	m_gis=NULL;
}

/**
	\brief 整个启动过程。

	包括：
	  -# 获取port列表。\n
	  -# 登录。\n
	  -# 上传SubServer及相关游戏相信。\n
*/
JSubServerStartup::EReturnValue JSubServerStartup::startup()const
{
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
	SHost gsiHost=m_ps->rqsServerPort(EST_SUBSERVER);
	m_gis->connectToHost(gsiHost.m_address,gsiHost.m_port);
	if(!m_gis->waitForConnected(1000))
	{
		qDebug()<<"game server connect failed . error :"
				<<m_gis->sendGsInfoError();
		return ERV_ConnectFailed;
	}
	JLoginHashCodeRecorder lhcr;
	m_gis->sendLoginHashCode(lhcr.getUserId(),lhcr.getCode());
	if(!m_gis->waitForLhc(1000))
	{
		qDebug()<<"1 gis pass Login Hash failed . error :"
				<<m_gis->sendGsInfoState()
				<<m_gis->sendGsInfoError();
		return ERV_PlhFailed;
	}
	if(m_gameinfo.m_gameId>0 && !m_gameinfo.m_name.isEmpty())
	{
		m_gis->sendGameInfo(m_gameinfo);
		if(!m_gis->waitForSend(1000))
		{
			qDebug()<<"send game info failed . error :"
					<<m_gis->sendGsInfoError();
			ret=ERV_SendFailed;
		}else{
			qDebug()<<"send game info success.";
		}
	}
	m_gis->sendServerInfo(m_serverinfo);
	if(!m_gis->waitForSend(1000))
	{
		qDebug()<<"send server info failed . error :"
				<<m_gis->sendGsInfoError();
		ret=ERV_SendFailed;
	}else{
		qDebug()<<"send server info success.";
	}
	m_gis->sendRelation(m_serverinfo.m_serverId,m_gameinfo.m_gameId,m_gameinfo.m_version);
	if(!m_gis->waitForSend(1000))
	{
		qDebug()<<"send relation failed . error :"
				<<m_gis->sendGsInfoError();
		ret=ERV_SendFailed;
	}else{
		qDebug()<<"send relation success.";
	}
	qDebug()<<m_serverinfo.m_name<<"startup success.";
	return ret;
}
