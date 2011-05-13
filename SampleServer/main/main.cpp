#include <QtCore/QCoreApplication>

#include "jargumentanalyse.h"
#include "service/jportservice.h"
#include "service/jloginservice2.h"
#include "service/jgsinfoservice.h"
#include "service/jcryprorecorder.h"
#include "sgame.h"

enum ERuturnValue{
    ERV_Success,
    ERV_ConnectFailed,
    ERV_LoginFailed,
    ERV_PlhFailed
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JArgumentAnalyse aa(argc,argv);
    JPortService ps;
    ps.setServerPort(EST_FREEPORT,SHost(aa.getAddress(),aa.getPort()));
    JLoginService2 login;
    SHost loginHost=ps.rqsServerPort(EST_LOGIN);
//    qDebug()<<loginHost.m_address<<loginHost.m_port;
    login.connectToHost(loginHost.m_address,loginHost.m_port);
    if(!login.waitForConnected(1000))
    {
        qDebug()<<"connect failed . error :"<<login.error();
        return ERV_ConnectFailed;
    }
    login.login("sampleserverrunner","123",ROLE_GAMESERVERRUNNER);
    if(!login.waitForLogined(1000))
    {
        qDebug()<<"Login failed . error :"<<login.error();
        return ERV_LoginFailed;
    }
//    qDebug()<<"game info socket"<<ps.rqsServerPort(EST_GAMEINFO).m_port;
    JGsInfoService gis;
    SHost gsiHost=ps.rqsServerPort(EST_GAMESERVER);
    gis.connectToHost(gsiHost.m_address,gsiHost.m_port);
    if(!gis.waitForConnected(1000))
    {
        qDebug()<<"game server connect failed . error :"
                <<gis.error();
        return ERV_ConnectFailed;
    }
    JCryproRecorder cr;
    gis.sendCrypro(cr.getUserId(),cr.getCrypro());
//    qDebug()<<gis.state();
    if(!gis.waitForPassLoginHash(1000))
    {
        qDebug()<<"gis pass Login Hash failed . error :"
                //<<cr.getUserId()<<cr.getCrypro().toHex().toUpper()
                <<gis.state()
                <<gis.error();
        return ERV_PlhFailed;
    }
    SGameInfo gi;
    {
        gi.m_gameId=109;
        gi.m_name="sample server";
        gi.m_author="elephant liu";
        gi.m_serverVersion=JVersion(1);
        gi.m_introduction="this is just a sample.";
    }
    gis.sendGsInfo(gi);
    qDebug()<<"game server startup success.";
    return a.exec();
}
