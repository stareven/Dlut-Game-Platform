#ifndef JGAMEINFOSOCKET_H
#define JGAMEINFOSOCKET_H

#include "jsocketbase.h"

#include "jglobal.h"

class QTcpSocket;
class QHostAddress;
namespace SubServer
{
	class SGameInfo2;
}
class JVersion;

class JGameInfoSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JGameInfoSocket(QObject *parent = 0);
    void sendCrypro(JID,const QByteArray&);
//    void rqsIdList();
	void rqsGameList();
	void rqsServers(JID gameId,const JVersion&);
protected:
    void dataProcess(const QByteArray&);
signals:
	void rcvPassLoginHash(bool);
	void rcvGameList(const QList<SubServer::SGameInfo2>&);
	void rcvServers(JID,const JVersion&,const QSet<JID>&);
//    void rcvGameInfo(const SGameInfo&);
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

//class QDataStream;

//QDataStream& operator>>(QDataStream& stream,SGameName&);

//QDataStream& operator>>(QDataStream& stream,SGameInfo&);

//QDataStream& operator>>(QDataStream& stream,JVersion& ver);

#endif // JGAMEINFOSOCKET_H
