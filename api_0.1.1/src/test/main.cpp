#include "../request/jrequestlogin.h"
#include "../request/jrequestuserinfo.h"

#include <QHostAddress>

int main(){
    JRequestLogin login;
    login.connectToHost(QHostAddress("127.0.0.1"),37373);
    login.login("a","b",ROLE_GAMEDESIGNER);
	bool rst = login.waitForLogined();
	qDebug()<<"rst="<<rst;

	JRequestUserInfo rui;
	JUserInfo ui = rui.pullUserInfo(1);
	qDebug()<<"user nickname="<<ui.getNickname();
	return 0;
}
