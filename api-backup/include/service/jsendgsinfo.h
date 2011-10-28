#ifndef JSENDGSINFO_H
#define JSENDGSINFO_H

#include "service/jlhcrequestbase.h"

#include "global/jglobal.h"

class QHostAddress;
class JSendGsInfoSocket;
class SGameInfo;
namespace SubServer
{
	class SSubServer;
	class SGameInfo2;
}
class JVersion;

class JSendGsInfo : public JLhcRequestBase
{
    Q_OBJECT
public:
	explicit JSendGsInfo(QObject *parent = 0);
	void sendServerInfo(const SubServer::SSubServer&);
	void sendGameInfo(const SubServer::SGameInfo2&);
	void sendRelation(JID serverId,JID gameId,const JVersion& gameVersion);
	/// \brief 发送状态
	enum ESgiState{
		ESS_Init, ///< 初始状态
		ESS_Sending, ///< 正在发送
		ESS_SendSuccess, ///< 发送成功
		ESS_Error ///< 发生错误
    };
	ESgiState sendGsInfoState()const;
    bool waitForSend(int msecs=30000);
	const QString& sendGsInfoError()const;
signals:
	void error(const QString&);
	void rcvSendCode(JID protocol,JCode code);
protected slots:
	void on_socket_rcvSendCode(JID protocol,JCode code);
private:
	ESgiState m_state;
	JSendGsInfoSocket* m_socket;
	int m_error;
};

#endif // JSENDGSINFO_H
