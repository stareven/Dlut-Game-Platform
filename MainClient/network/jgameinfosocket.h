#ifndef JGAMEINFOSOCKET_H
#define JGAMEINFOSOCKET_H

#include "jsocketbase.h"

#include "sgame.h"
#include "jglobal.h"

class QTcpSocket;
class QHostAddress;

class JGameInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JGameInfoSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
    void rqsIdList();
    void rqsNameList();
    void rqsGameInfo(JID);
protected:
    void dataProcess(const QByteArray&);
signals:
    void rcvPassLoginHash(bool);
    void rcvIdList(const QList<JID>&);
    void rcvNameList(const QList<SGameName>&);
    void rcvGameInfo(const SGameInfo&);
//private:
//    bool m_passLoginHash;
//    QList<JID> m_idlist;
//    QList<SGameName> m_namelist;
//    SGameInfo m_gameinfo;
//public:
//    bool isPLH()const;//pass login hash
//    const QList<JID>& getIdList()const;
//    const QList<SGameName>& getNameList()const;
//    const SGameInfo& getGameInfo()const;
};

class QDataStream;

QDataStream& operator>>(QDataStream& stream,SGameName&);

QDataStream& operator>>(QDataStream& stream,SGameInfo&);

QDataStream& operator>>(QDataStream& stream,JVersion& ver);

#endif // JGAMEINFOSOCKET_H
