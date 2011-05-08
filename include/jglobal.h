#ifndef JGLOBAL_H
#define JGLOBAL_H

#include <QtGlobal>

typedef qint16 JRole;
const JRole ROLE_GAMEPLAYER=JRole(1)<<0;
const JRole ROLE_GAMEDESIGNER=JRole(1)<<1;
const JRole ROLE_ADMIN=JRole(1)<<2;
const JRole ROLE_ROOT=JRole(1)<<3;
typedef qint32 JID;
typedef qint16 JCode;

enum ENet{
    EN_CONNECTED,
    EN_DISCONNECTED
};

#endif // JGLOBAL_H
