#include "sgame.h"

#include <QDataStream>

QDataStream& operator<<(QDataStream& stream,const SGameName& gn)
{
    stream<<(JID)gn.m_gameId;
    stream<<gn.m_name;
    return stream;
}

QDataStream& operator<<(QDataStream& stream,const SGameInfo& gi)
{
    stream<<(SGameName)gi;
    stream<<gi.m_author;
    stream<<gi.m_serverVersion;
    stream<<gi.m_localVersion;
    stream<<gi.m_introduction;
    return stream;
}

QDataStream& operator<<(QDataStream& stream,const JVersion& ver)
{
    stream<<ver.m_data;
    return stream;
}


QDataStream& operator>>(QDataStream& stream,SGameName& gn)
{
    stream>>gn.m_gameId;
    stream>>gn.m_name;
    return stream;
}

QDataStream& operator>>(QDataStream& stream,SGameInfo& gi)
{
    stream>>(SGameName&)gi;
    stream>>gi.m_author;
    stream>>gi.m_serverVersion;
    stream>>gi.m_localVersion;
    stream>>gi.m_introduction;
    return stream;
}

QDataStream& operator>>(QDataStream& stream,JVersion& ver)
{
    stream>>ver.m_data;
    return stream;
}
