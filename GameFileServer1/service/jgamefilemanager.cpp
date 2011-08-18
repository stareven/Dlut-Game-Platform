#include "jgamefilemanager.h"

JGameFileManager::JGameFileManager()
{
}

QString JGameFileManager::getFilePath(const QString&,const JVersion&)
{
#ifdef Q_OS_WIN32
	return "../SnakeClient-build-desktop/debug/SnakeClient.exe";
#else
	return "../SnakeClient-build-desktop/SnakeClient";
#endif
}
