#include "ClientRequest/JRequestLogin"
#include "ClientRequest/JRequestUserInfo"
#include "ClientRequest/JRequestGameInfo"
#include "ClientRequest/JRequestServerInfo"
#include "ClientRequest/JUploadGameInfo"
#include "ClientRequest/JUploadServerInfo"
#include "Socket/JMainClientSocket"
#include <Session/JSession>
#include <ClientRequest/JRequestUserRegister>
#include <Helper/JConnectHelper>

#include <QHostAddress>
#include <QCoreApplication>

int main(int argc, char *argv[]){
	QCoreApplication app(argc,argv);
	JConnectHelper connectHelper(JMainClientSocket::getInstance());
	connectHelper.connectToHost(SHost(QHostAddress::LocalHost,37373));
	if(!connectHelper.waitForConnected(1000)){
		qDebug()<<connectHelper.getConnectError()<<JMainClientSocket::getInstance()->socketState();
		return 1;
	}

	JRequestUserRegister reg;
	reg.sendRegister("tryregister","register");
	if(!reg.waitForRegisterResult(1000)){
		qDebug()<<"register failed"<<reg.getRegisterError();
		return 1;
	}

	JRequestLogin login;
	login.login("tryregister","register",ROLE_GAMEPLAYER);
	bool rst = login.waitForLogined(1000);
	qDebug()<<"rst="<<rst<<" login error:"<<login.getLoginError();
	qDebug()<<"user id = "<<JMainClientSocket::getInstance()->getSession()->getUserId()
			<<"login hash code = "<<JMainClientSocket::getInstance()->getSession()->getLoginHashCodeStr();

	JRequestUserInfo rui;
	JUserInfo ui = rui.pullUserInfo(1,1000);
	qDebug()<<"user nickname="<<ui.getNickname();

	JRequestGameInfo rgi;
	JGameInfo gi = rgi.pullGameInfo(1,1000);
	qDebug()<<"game name="<<gi.getName();
	JGameList gl = rgi.pullGameList(1000);
	qDebug()<<"game list="<<gl;

	JRequestServerInfo rsi;
	JServerInfo si = rsi.pullServerInfo(1,1000);
	qDebug()<<"server name="<<si.getName();

	JUploadGameInfo ugi;
	JGameInfo uploadGameInfo(1,"upload",JVersion(),1,1,"upload introduction",1,QUrl());
	JCode code_ugi=ugi.pushGameInfo(uploadGameInfo,1000);
	qDebug()<<"upload game info:"<<code_ugi;

	JUploadServerInfo usi;
	JServerInfo uploadServerInfo(1,"upload",1,SHost());
	JCode code_usi=usi.pushServerInfo(uploadServerInfo,1000);
	qDebug()<<"upload server info:"<<code_usi;
	return 0;
}
