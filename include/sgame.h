#ifndef SGAME_H
#define SGAME_H

#include <QString>
#include "jglobal.h"
#include "jversion.h"

struct SGameName
{
    SGameName():m_gameId(-1){}
    JID m_gameId;
    QString m_name;
};

struct SGameInfo : public SGameName
{
    QString m_author;
    JVersion m_serverVersion;
    JVersion m_localVersion;
    QString m_introduction;
};

class QDataStream;

QDataStream& operator<<(QDataStream& stream,const SGameName&);

QDataStream& operator<<(QDataStream& stream,const SGameInfo&);

QDataStream& operator<<(QDataStream& stream,const JVersion& ver);

QDataStream& operator>>(QDataStream& stream,SGameName&);

QDataStream& operator>>(QDataStream& stream,SGameInfo&);

QDataStream& operator>>(QDataStream& stream,JVersion& ver);


#endif // SGAME_H
