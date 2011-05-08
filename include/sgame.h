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

#endif // SGAME_H
