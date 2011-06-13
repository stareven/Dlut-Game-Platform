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
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
//    QList<JID> m_idList;
	QList<SubServer::SGameInfo2> m_gameList;
public:
//    const QList<JID>& getIdList()const;
//    const QList<SGameName>& getNameList()const;
	const QList<SubServer::SGameInfo2>& getGameList()const;
	SubServer::SGameInfo2 getGameInfo(JID gameid)const;
};

#endif // JGAMEINFOSERVICE_H
