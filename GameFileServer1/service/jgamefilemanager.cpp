#include "jgamefilemanager.h"

JGameFileManager::JGameFileManager()
{
}

QString JGameFileManager::getFilePath(const QString&,const JVersion&)
{
	return "../SnakeClient-build-desktop/SnakeClient";
}
