#ifndef JSENDGSINFOSOCKET_H
#define JSENDGSINFOSOCKET_H

#include "jlhcsocketbase.h"

namespace SubServer
{
	class SSubServer;
	class SGameInfo2;
}
class JVersion;

class JSendGsInfoSocket : public JLhcSocketBase
{
    Q_OBJECT
public:
	explicit JSendGsInfoSocket(QObject *parent = 0);
	void sendServerInfo(const SubServer::SSubServer&);
	void sendGameInfo(const SubServer::SGameInfo2&);
	void sendRelation(JID serverId,JID gameId,const JVersion& gameVersion);
protected:
	void afterLhc(const QByteArray&);
signals:
	void rcvSendCode(JID protocol,JCode code);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UploadSubServer;
	}
};

#endif // JSENDGSINFOSOCKET_H
