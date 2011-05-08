#ifndef JGAMEINFOSERVICE_H
#define JGAMEINFOSERVICE_H

#include <QObject>
#include <QMap>

#include "jglobal.h"
#include "sgame.h"

class JGameInfoSocket;

class JGameInfoService : public QObject
{
    Q_OBJECT
public:
    explicit JGameInfoService(QObject *parent = 0);

    void rqsIdList();
    void rqsNameList();
    void rqsGameInfo(JID);
protected:
    bool passLoginHash();
signals:
    void idListReady();
    void nameListReady();
    void gameInfoReady(JID gameid);
private:
    JGameInfoSocket* m_socket;
protected slots:
    void on_socket_rcvPassLoginHash(bool);
    void on_socket_rcvIdList(const QList<JID>&);
    void on_socket_rcvNameList(const QList<SGameName>&);
    void on_socket_rcvGameInfo(const SGameInfo&);
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
    QList<JID> m_idList;
    QList<SGameName> m_nameList;
    QMap<JID,SGameInfo> m_gameInfos;
public:
    const QList<JID>& getIdList()const;
    const QList<SGameName>& getNameList()const;
    SGameInfo getGameInfo(JID gameid)const;
};

#endif // JGAMEINFOSERVICE_H
