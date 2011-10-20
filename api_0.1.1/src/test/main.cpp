#include "../request/jrequestlogin.h"
#include "../request/jrequestuserinfo.h"
#include "../request/jrequestgameinfo.h"
#include "../request/jrequestserverinfo.h"

#include <QHostAddress>

int main(){
    JRequestLogin login;
    login.connectToHost(QHostAddress("127.0.0.1"),37373);
    login.login("a","b",ROLE_GAMEDESIGNER);
	bool rst = login.waitForLogined(1000);
	qDebug()<<"rst="<<rst;

	JRequestUserInfo rui;
	JUserInfo ui = rui.pullUserInfo(1,1000);
	qDebug()<<"user nickname="<<ui.getNickname();

	JRequestGameInfo rgi;
	JGameInfo gi = rgi.pullGameInfo(1,1000);
	qDebug()<<"game name="<<gi.getName();

	JRequestServerInfo rsi;
	JServerInfo si = rsi.pullServerInfo(1,1000);
	qDebug()<<"game name="<<si.getName();
	return 0;
}
