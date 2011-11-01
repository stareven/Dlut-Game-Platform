#ifndef JREQUESTGAMEINFOSOCKET_H
#define JREQUESTGAMEINFOSOCKET_H

#include "network/jsocketbase.h"

#include <Global/Global>

class QTcpSocket;
class QHostAddress;
namespace SubServer
{
	class SGameInfo2;
	class SSubServer;
}
class JVersion;

class JRequestGameInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JRequestGameInfoSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
	void rqsGameList();
	void rqsServers(JID gameId,const JVersion&);
	void rqsServerInfo(JID serverId);
protected:
    void dataProcess(const QByteArray&);
signals:
	void rcvPassLoginHash(bool);
	void rcvGameList(const QList<SubServer::SGameInfo2>&);
	void rcvServers(JID,const JVersion&,const QSet<JID>&);
	void rcvServerInfo(const SubServer::SSubServer&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_GetGameInfo;
	}
};

#endif // JREQUESTGAMEINFOSOCKET_H
