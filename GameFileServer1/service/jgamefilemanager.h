#ifndef JGAMEFILEMANAGER_H
#define JGAMEFILEMANAGER_H

#include <QString>
class JVersion;
class JGameFileManager
{
public:
    JGameFileManager();
	QString getFilePath(const QString& gamename,const JVersion& version);
};

#endif // JGAMEFILEMANAGER_H
