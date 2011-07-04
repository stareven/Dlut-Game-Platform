#ifndef JGLOBALSETTINGS_H
#define JGLOBALSETTINGS_H

#include <QHostAddress>

#include "global/jglobal.h"

namespace GlobalSettings
{
	struct SHost{
		SHost(){}
		SHost(const QHostAddress& address,quint16 port)
		{
			m_address=address;
			m_port=port;
		}
		QHostAddress m_address;
		quint16 m_port;
	};

	extern JID g_userId;
	extern SHost g_gameServer;
	extern SHost g_mainServer;
}

#endif // JGLOBALSETTINGS_H
