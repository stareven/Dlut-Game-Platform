#include "jglobalsettings.h"

SHost GlobalSettings::g_mainServer(QHostAddress("127.0.0.1"),37373);
SHost GlobalSettings::g_gameServer(QHostAddress("127.0.0.1"),60373);
JID GlobalSettings::g_userId;
QByteArray GlobalSettings::g_loginhashcode;
