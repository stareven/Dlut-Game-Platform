#include "ClientRequest/JRequestLogin"
#include "ClientRequest/JRequestUserInfo"
#include "ClientRequest/JRequestGameInfo"
#include "ClientRequest/JRequestServerInfo"
#include "ClientRequest/JUploadGameInfo"
#include "ClientRequest/JUploadServerInfo"
#include "Socket/JClientSocketBase"

#include <QHostAddress>
#include <QCoreApplication>

int main(int argc, char *argv[]){
	QCoreApplication app(argc,argv);
    JRequestLogin login;
	login.connectToHost(QHostAddress::LocalHost,37373);
	if(!login.waitForConnected(1000)){
		qDebug()<<login.getConnectError()<<JClientSocketBase::getInstance()->socketState();
		return 1;
	}
	login.login("elephant","acm",ROLE_GAMEPLAYER);
	bool rst = login.waitForLogined(1000);
	qDebug()<<"rst="<<rst<<" login error:"<<login.getLoginError();

	JRequestUserInfo rui;
	JUserInfo ui = rui.pullUserInfo(1,1000);
	qDebug()<<"user nickname="<<ui.getNickname();

	JRequestGameInfo rgi;
	JGameInfo gi = rgi.pullGameInfo(1,1000);
	qDebug()<<"game name="<<gi.getName();

	JRequestServerInfo rsi;
	JServerInfo si = rsi.pullServerInfo(1,1000);
	qDebug()<<"server name="<<si.getName();

	JUploadGameInfo ugi;
	JCode code_ugi=ugi.pushGameInfo(gi,1000);
	qDebug()<<"upload game info:"<<code_ugi;

	JUploadServerInfo usi;
	JCode code_usi=usi.pushServerInfo(si,1000);
	qDebug()<<"upload server info:"<<code_usi;
	return 0;
}
