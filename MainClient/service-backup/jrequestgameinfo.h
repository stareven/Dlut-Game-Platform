#ifndef JREQUESTGAMEINFO_H
#define JREQUESTGAMEINFO_H

#include <QObject>
#include <QMap>

#include <Global/Global>

class JRequestGameInfoSocket;

#include "global/ssubserver.h"

class JRequestGameInfo : public QObject
{
    Q_OBJECT
public:
    explicit JRequestGameInfo(QObject *parent = 0);
	void rqsGameList();
	void rqsGameInfo(JID);
	void rqsServerList(JID gameId,const JVersion&);
	void rqsServerInfo(JID serverId);
protected:
    bool passLoginHash();
signals:
	void gameListReady();
	void gameInfoReady(JID gameid);
private:
    JRequestGameInfoSocket* m_socket;
protected slots:
    void on_socket_rcvPassLoginHash(bool);
	void on_socket_rcvGameList(const QList<SubServer::SGameInfo2>&);
	void on_socket_rcvServers(JID,const JVersion&,const QSet<JID>&);
	void on_socket_rcvServerInfo(SubServer::SSubServer);
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
	QMap<JID,SubServer::SGameInfo2> m_games;
	QMap<JID,QSet<JID> > m_relations;
	QMap<JID,SubServer::SSubServer> m_servers;
public:
	const QMap<JID,SubServer::SGameInfo2>& getGames()const;
	SubServer::SGameInfo2 getGameInfo(JID gameid)const;
	QSet<JID> getServerListOnGame(JID gameId)const;
	SubServer::SSubServer getServerInfo(JID serverId)const;
};

#endif // JREQUESTGAMEINFO_H
