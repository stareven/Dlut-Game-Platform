#include <QtCore/QCoreApplication>

#include <QDebug>

#include "network/jgfsserver.h"
#include "service/jsubserverstartup.h"
#include "global/elogin.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	JGfsServer server;
	quint16 port=server.run(50123);
	qDebug()<<"GameFileServer1 startup :"<<port;
	JSubServerStartup sssu;
	sssu.m_host.m_address=QHostAddress("127.0.0.1");
	sssu.m_host.m_port=37373;
	sssu.m_loginname="sampleserverrunner";
	sssu.m_passwd="123";
	sssu.m_role=ROLE_GAMESERVERRUNNER;
	sssu.m_gameinfo.m_gameId=109;
	sssu.m_gameinfo.m_version=JVersion(1);
	sssu.m_serverinfo.m_serverId=53380;
	sssu.m_serverinfo.m_name="game_file_server_1";
	sssu.m_serverinfo.m_address=QHostAddress::LocalHost;
	sssu.m_serverinfo.m_port=port;
	sssu.m_serverinfo.m_type=SubServer::SSubServer::ET_GameFileServer;
	sssu.startup();
    return a.exec();
}
