#ifndef JGAMEINFOSERVICE_H
#define JGAMEINFOSERVICE_H

#include <QObject>
#include <QMap>

#include "jglobal.h"

class JGameInfoSocket;

#include "ssubserver.h"

class JGameInfoService : public QObject
{
    Q_OBJECT
public:
    explicit JGameInfoService(QObject *parent = 0);

//    void rqsIdList();
	void rqsGameList();
	void rqsGameInfo(JID);
	void rqsServers(JID gameId,const JVersion&);
protected:
    bool passLoginHash();
signals:
//    void idListReady();
	void gameListReady();
	void gameInfoReady(JID gameid);
private:
    JGameInfoSocket* m_socket;
protected slots:
    void on_socket_rcvPassLoginHash(bool);
//    void on_socket_rcvIdList(const QList<JID>&);
	void on_socket_rcvGameList(const QList<SubServer::SGameInfo2>&);
//	void on_socket_rcvGameList(const SubServer::SGameInfo2&);
	void on_socket_rcvServers(JID,const JVersion&,const QSet<JID>&);
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
//    QList<JID> m_idList;
//	QList<SubServer::SGameInfo2> m_gameList;
	QMap<JID,SubServer::SGameInfo2> m_games;
public:
//    const QList<JID>& getIdList()const;
//    const QList<SGameName>& getNameList()const;
	const QMap<JID,SubServer::SGameInfo2>& getGames()const;
	SubServer::SGameInfo2 getGameInfo(JID gameid)const;
};

#endif // JGAMEINFOSERVICE_H
