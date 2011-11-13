#ifndef JGLOBALSETTINGS_H
#define JGLOBALSETTINGS_H

#include <QHostAddress>

#include <Global/Global>
#include <DataStruct/SHost>

namespace GlobalSettings
{
	extern SHost g_mainServer;
	extern SHost g_gameServer;
	extern JID g_userId;
	extern QByteArray g_loginhashcode;
}

#endif // JGLOBALSETTINGS_H
