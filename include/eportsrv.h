#ifndef EPORTSRV_H
#define EPORTSRV_H

enum EPSProtocol{EPP_LOGINHASH,EPP_PORT};
enum EServerType{
    EST_LOGIN,
    EST_GAMEINFO,
    EST_FREEPORT,
    EST_SECRETPORT,
    EST_GAMESERVER,
	EST_SUBSERVER,
    EST_MAX
};

#define isInFree(type) ( EST_LOGIN==type || EST_SECRETPORT== type)

#include <QHostAddress>

struct SHost
{
    SHost(){}
    SHost(const QHostAddress& address,quint16 port)
    {
        m_address=address;
        m_port=port;
    }
    QHostAddress m_address;
    quint16 m_port;
};

#endif // EPORTSRV_H
