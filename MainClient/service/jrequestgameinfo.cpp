#include "jrequestgameinfo.h"

#include <QCoreApplication>
#include "global/jelapsedtimer.h"
#include <QDebug>
#include <QHostAddress>

#include "network/jrequestgameinfosocket.h"
#include "service/jcryprorecorder.h"
#include "service/jrequestport.h"

JRequestGameInfo::JRequestGameInfo(QObject *parent) :
    QObject(parent)
{
    m_socket=new JRequestGameInfoSocket(this);
    connect(m_socket,SIGNAL(rcvPassLoginHash(bool)),SLOT(on_socket_rcvPassLoginHash(bool)));
//    connect(m_socket,SIGNAL(rcvIdList(QList<JID>)),SLOT(on_socket_rcvIdList(QList<JID>)));
//    connect(m_socket,SIGNAL(rcvNameList(QList<SGameName>)),SLOT(on_socket_rcvNameList(QList<SGameName>)));
//    connect(m_socket,SIGNAL(rcvGameInfo(SGameInfo)),SLOT(on_socket_rcvGameInfo(SGameInfo)));
	connect(m_socket,SIGNAL(rcvGameList(QList<SubServer::SGameInfo2>)),SLOT(on_socket_rcvGameList(QList<SubServer::SGameInfo2>)));
	connect(m_socket,SIGNAL(rcvServers(JID,JVersion,QSet<JID>)),SLOT(on_socket_rcvServers(JID,JVersion,QSet<JID>)));
	connect(m_socket,SIGNAL(rcvServerInfo(SubServer::SSubServer)),SLOT(on_socket_rcvServerInfo(SubServer::SSubServer)));
    m_plh=-1;
	JRequestPort ps;
    SHost host=ps.rqsServerPort(EST_GAMEINFO);
    m_socket->connectToHost(host.m_address,host.m_port);
}

//void JRequestGameInfo::rqsIdList()
//{
////    JCryproRecorder cr;
////    if(cr.getUserId()==-1 || cr.getCrypro().isEmpty())
////    {
////        qDebug()<<"JRequestGameInfo::rqsIdList : have not record the login hash . can not request id list!";
////        return ;
////    }else{
////        int i;
////        m_socket->sendCrypro(cr.getUserId(),cr.getCrypro());
////        for(i=0;i<50;++i)
////        {
////            if(m_plh!=-1)
////            {
////                break;
////            }
////        }
////        if(50==i)
////        {
////            qDebug()<<"pass login hash time out .";
////            return;
////        }
////        if(m_plh==0)
////        {
////            qDebug()<<"pass login hash failed .";
////            return;
////        }
////    }
//    if(!passLoginHash()) return;
//    m_socket->rqsIdList();
//}

void JRequestGameInfo::rqsGameList()
{
//    JCryproRecorder cr;
//    if(cr.getUserId()==-1 || cr.getCrypro().isEmpty())
//    {
//        qDebug()<<"JRequestGameInfo::rqsIdList : have not record the login hash . can not request id list!";
//    }
	if(!passLoginHash()) return;
	m_socket->rqsGameList();
}

void JRequestGameInfo::rqsGameInfo(JID id)
{
//    JCryproRecorder cr;
//    if(cr.getUserId()==-1 || cr.getCrypro().isEmpty())
//    {
//        qDebug()<<"JRequestGameInfo::rqsIdList : have not record the login hash . can not request id list!";
//    }
//    if(!passLoginHash()) return;
//    m_socket->rqsGameInfo(id);
	emit gameInfoReady(id);
}

void JRequestGameInfo::rqsServerList(JID gameId,const JVersion& version)
{
	if(!passLoginHash()) return;
	m_socket->rqsServers(gameId,version);
}

void JRequestGameInfo::rqsServerInfo(JID serverId)
{
	if(!passLoginHash()) return;
	m_socket->rqsServerInfo(serverId);
}

bool JRequestGameInfo::passLoginHash()
{
    JElapsedTimer t;
    JCryproRecorder cr;
    t.start();
    while(t.elapsed()<1000)
    {
        switch(m_plh)
        {
        case 1:
            return true;
            break;
        case 0:
            return false;
            break;
        case -1:
            if(cr.getUserId()==-1 || cr.getCrypro().isEmpty())
            {
                qDebug()<<"JRequestGameInfo::rqsIdList : have not record the login hash . can not request id list!";
                return false;
            }
            if(m_socket->isConnected())
            {
                m_socket->sendCrypro(cr.getUserId(),cr.getCrypro());
                m_plh=-2;
            }
            break;
        case -2:
            break;
        }

        QCoreApplication::processEvents();
    }
    return false;
}

void JRequestGameInfo::on_socket_rcvPassLoginHash(bool plh)
{
	qDebug()<<"JRequestGameInfo::on_socket_rcvPassLoginHash : "<<plh;
    m_plh=plh;
}

//void JRequestGameInfo::on_socket_rcvIdList(const QList<JID>& idlist)
//{
////    qDebug()<<"JRequestGameInfo::on_socket_rcvIdList : "<<idlist.size();
//    m_idList=idlist;
//    emit idListReady();
//}

void JRequestGameInfo::on_socket_rcvGameList(const QList<SubServer::SGameInfo2>& gamelist)
{
	qDebug()<<"JRequestGameInfo::on_socket_rcvGameList : "<<gamelist.size();
//	m_gameList=gamelist;
	foreach(SubServer::SGameInfo2 gi,gamelist)
	{
		m_games.insert (gi.m_gameId,gi);
	}

	emit gameListReady();
}

void JRequestGameInfo::on_socket_rcvServers(JID gameId,const JVersion& version,const QSet<JID>& servers)
{
	qDebug()<<gameId<<version.getData()<<servers;
	SubServer::SGameInfo2 gi=getGameInfo(gameId);
	if(version!=gi.m_version)
	{
		qDebug()<<"JRequestGameInfo::on_socket_rcvServers : version not match";
		return;
	}
	foreach(JID serverId,servers)
	{
		rqsServerInfo(serverId);
	}
	m_relations[gameId].unite(servers);
}

void JRequestGameInfo::on_socket_rcvServerInfo(const SubServer::SSubServer& si)
{
	m_servers.insert(si.m_serverId,si);
}

//void JRequestGameInfo::on_socket_rcvGameInfo(const SGameInfo& gi)
//{
////    qDebug()<<"JRequestGameInfo::on_socket_rcvGameInfo : "<<gi.m_gameId;
//    m_gameInfos.insert(gi.m_gameId,gi);
//    emit gameInfoReady(gi.m_gameId);
//}

//const QList<JID>& JRequestGameInfo::getIdList()const
//{
//    return m_idList;
//}

const QMap<JID,SubServer::SGameInfo2>& JRequestGameInfo::getGames()const
{
	return m_games;
}

SubServer::SGameInfo2 JRequestGameInfo::getGameInfo(JID gameid)const
{
	return m_games.value(gameid);
}

QSet<JID> JRequestGameInfo::getServerListOnGame(JID gameId)const
{
	return m_relations.value(gameId);
}

SubServer::SSubServer JRequestGameInfo::getServerInfo(JID serverId)const
{
	return m_servers.value(serverId);
}
