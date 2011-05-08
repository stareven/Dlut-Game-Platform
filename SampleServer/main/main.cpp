#include <QtCore/QCoreApplication>

#include "jargumentanalyse.h"
#include "service/jportservice.h"
#include "service/jloginservice2.h"

enum ERuturnValue{
    ERV_Success,
    ERV_ConnectFailed,
    ERV_LoginFailed
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JArgumentAnalyse aa(argc,argv);
    JPortService ps;
    ps.setServerPort(EST_FREEPORT,SHost(aa.getAddress(),aa.getPort()));
    JLoginService2 login;
    SHost loginHost=ps.rqsServerPort(EST_LOGIN);
    qDebug()<<loginHost.m_address<<loginHost.m_port;
    login.connectToHost(loginHost.m_address,loginHost.m_port);
    if(!login.waitForConnected(1000))
    {
        qDebug()<<"connect failed . error :"<<login.error();
        return ERV_ConnectFailed;
    }
    login.login("jdmd","jdmd",ROLE_GAMEDESIGNER);
    if(!login.waitForLogined(1000))
    {
        qDebug()<<"Login failed . error :"<<login.error();
        return ERV_LoginFailed;
    }
    return a.exec();
}
