#include "jglobalsettings.h"

GlobalSettings::SHost GlobalSettings::g_mainServer(QHostAddress("127.0.0.1"),37373);
GlobalSettings::SHost GlobalSettings::g_gameServer(QHostAddress("127.0.0.1"),60373);
