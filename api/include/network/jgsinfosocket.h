#ifndef JGSINFOSOCKET_H
#define JGSINFOSOCKET_H

#include "jsocketbase.h"

namespace SubServer
{
	class SSubServer;
	class SGameInfo2;
}
class JVersion;

class JGsInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JGsInfoSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
//    void sendGsInfo(const SGameInfo&);
	void sendServerInfo(const SubServer::SSubServer&);
	void sendGameInfo(const SubServer::SGameInfo2&);
	void sendRelation(JID serverId,JID gameId,const JVersion& gameVersion);
protected:
    void dataProcess(const QByteArray&);
signals:
	void rcvPassLoginHash(bool);
	void rcvSendCode(JID protocol,JCode code);
};

#endif // JGSINFOSOCKET_H
