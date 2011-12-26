#include <QtCore/QCoreApplication>

#include <Helper/JGameServerStartup>
#include "jargumentanalyse.h"

#include "network/jsnakeserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JArgumentAnalyse aa(argc,argv);
	JSnakeServer server;
	server.run(60373);
	quint16 port=server.serverPort();
	qDebug()<<"snake server :"<<port;
	JGameServerStartup gssu;
	gssu.m_mainserver = SHost(aa.getAddress(),aa.getPort());
	gssu.m_loginname="sampleserverrunner";
    gssu.m_passwd="123456";
	gssu.m_role=ROLE_GAMESERVERRUNNER;
	gssu.m_gameinfo=JGameInfo(
				109,
				"Multi Snake",
				JVersion(1),
				901,
				902,
				"A snake game that multiplayer can play together",
				53379,
				QUrl("http://127.0.0.1/dgp/SnakeClient/SnakeClient"));
	gssu.m_serverinfo=JServerInfo(
				53379,
				"Multi Snake server",
				902,
				SHost(QHostAddress("127.0.0.1"),60373));
	JGameServerStartup::EReturnValue ret=gssu.startup();
	if(ret !=JGameServerStartup::ERV_Success)
	{
		return ret;
	}
    return a.exec();
}
