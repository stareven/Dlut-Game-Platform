#include "jgameinfosrv.h"

#include <QObject>
#include <QMap>

//SGameInfo createGI(JID id,
//                   const QString& name,
//                   const QString& author,
//                   const JVersion& sv,
//                   const JVersion& lv,
//                   const QString& intro)
//{
//    SGameInfo gi;
//    gi.m_gameId=id;
//    gi.m_name=name;
//    gi.m_author=author;
//    gi.m_serverVersion=sv;
//    gi.m_localVersion=lv;
//    gi.m_introduction=intro;
//    return gi;
//}

//SGameInfo gameinfos[]={
//    createGI(35,QObject::tr("elephant 35"),QObject::tr("elephant"),JVersion(1),JVersion(1),QObject::tr("no introduction")),
//    createGI(57,QObject::tr("elephant 57"),QObject::tr("elephant"),JVersion(1),JVersion(1),QObject::tr("no introduction"))
//};

//QList<SGameInfo> list_gameinfo;

QMap<QString,JID> map_name_id;
QMap<JID,SGameInfo> map_gameinfo;

QList<JID> JGameInfoSrv::JGis4Player::getIdList()const
{
    return map_gameinfo.keys();
//    QList<JID> ans;
////    int n=sizeof(gameinfos)/sizeof(SGameInfo);
//    int n=list_gameinfo.size();
//    int i;
//    for(i=0;i<n;++i)
//    {
//        ans.append(list_gameinfo[i].m_gameId);
//    }
//    return ans;
}

QList<SGameName> JGameInfoSrv::JGis4Player::getNameList()const
{
    QMap<JID,SGameInfo>::const_iterator it;
    QList<SGameName> ans;
    for(it=map_gameinfo.begin();it!=map_gameinfo.end();++it)
    {
        ans.append(it.value());
    }
    return ans;
////    int n=sizeof(gameinfos)/sizeof(SGameInfo);
//    int n=list_gameinfo.size();
//    int i;
//    for(i=0;i<n;++i)
//    {
//        ans.append(list_gameinfo[i]);
//    }
//    return ans;
}

SGameInfo JGameInfoSrv::JGis4Player::getInfoById(JID id)const
{
    return map_gameinfo.value(id);
//    SGameInfo ans;
////    int n=sizeof(gameinfos)/sizeof(SGameInfo);
//    int n=list_gameinfo.size();
//    int i;
//    for(i=0;i<n;++i)
//    {
//        if(list_gameinfo[i].m_gameId==id)
//        {
//            ans=list_gameinfo[i];
//            break;
//        }
//    }
//    return ans;
}

JCode JGameInfoSrv::JGis4Admin::addGame(SGameInfo& gi)const
{
    if(map_name_id.contains(gi.m_name)) return 1;
    if(map_gameinfo.contains(gi.m_gameId))
    {
        if(gi.m_gameId<GameidMin) gi.m_gameId=GameidMin;
        while(map_gameinfo.contains(gi.m_gameId)
            && gi.m_gameId<GameidMax)
        {
            ++gi.m_gameId;
        }
        if(gi.m_gameId==GameidMax)
        {
            gi.m_gameId=-1;
            return 2;
        }
    }
//    list_gameinfo.push_back(gi);
    map_name_id.insert(gi.m_name,gi.m_gameId);
    map_gameinfo.insert(gi.m_gameId,gi);
    return 0;
}

JCode JGameInfoSrv::JGis4Admin::deleteGame(JID id)const
{
    if(!map_gameinfo.contains(id)) return 1;
    map_name_id.remove(map_gameinfo.value(id).m_name);
    map_gameinfo.remove(id);
    return 0;
//    int i;
//    for(i=0;i<list_gameinfo.size();++i)
//    {
//        if(list_gameinfo.at(i).m_gameId==id)
//        {
//            break;
//        }
//    }
//    if(list_gameinfo.size()==i) return 1;
//    list_gameinfo.removeAt(i);
    return 0;
}

//#include <QDataStream>

//QDataStream& operator<<(QDataStream& stream,const SGameName& gn)
//{
//    stream<<(JID)gn.m_gameId;
//    stream<<gn.m_name;
//    return stream;
//}

//QDataStream& operator<<(QDataStream& stream,const SGameInfo& gi)
//{
//    stream<<(SGameName)gi;
//    stream<<gi.m_author;
//    stream<<gi.m_serverVersion;
//    stream<<gi.m_localVersion;
//    stream<<gi.m_introduction;
//    return stream;
//}

//QDataStream& operator<<(QDataStream& stream,const JVersion& ver)
//{
//    stream<<ver.m_data;
//    return stream;
//}
