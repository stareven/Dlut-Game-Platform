#ifndef JSENDGSINFOSOCKET_H
#define JSENDGSINFOSOCKET_H

#include "jsocketbase.h"

namespace SubServer
{
	class SSubServer;
	class SGameInfo2;
}
class JVersion;

class JSendGsInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JSendGsInfoSocket(QObject *parent = 0);
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
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UploadSubServer;
	}
};

#endif // JSENDGSINFOSOCKET_H
