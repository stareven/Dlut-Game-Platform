#include <QtCore/QCoreApplication>

#include "jargumentanalyse.h"
#include "service/jsubserverstartup.h"
#include "global/elogin.h"

#include "network/jsnakeserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JArgumentAnalyse aa(argc,argv);
	JSnakeServer server;
	server.run(60373);
	quint16 port=server.serverPort();
	qDebug()<<"snake server :"<<port;
	JSubServerStartup sssu;
	sssu.m_host.m_address=aa.getAddress();
	sssu.m_host.m_port=aa.getPort();
	sssu.m_loginname="sampleserverrunner";
	sssu.m_passwd="123";
	sssu.m_role=ROLE_GAMESERVERRUNNER;
	sssu.m_gameinfo.m_gameId=109;
	sssu.m_gameinfo.m_name="Multi Snake";
	sssu.m_gameinfo.m_author=901;
	sssu.m_gameinfo.m_version=JVersion(1);
	sssu.m_gameinfo.m_introduction="A snake game that multiplayer can play together";
	sssu.m_serverinfo.m_serverId=53379;
	sssu.m_serverinfo.m_name="Multi Snake server";
	sssu.m_serverinfo.m_address=QHostAddress::LocalHost;
	sssu.m_serverinfo.m_port=port;
	sssu.m_serverinfo.m_type=SubServer::SSubServer::ET_GameServer;
	sssu.startup();
//	if(ret!=JSubServerStartup::ERV_Success)
//	{
//		return ret;
//	}
    return a.exec();
}
