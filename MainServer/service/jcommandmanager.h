#ifndef JCOMMANDMANAGER_H
#define JCOMMANDMANAGER_H

#include <Global/Global>

class JCommandManager
{
public:
    JCommandManager();
	void executeCommand(JID type,JID param1);
protected:
	void shutdownMainServer();
	void restartMainServer();
};

#endif // JCOMMANDMANAGER_H
