#include "jcommandmanager.h"

#include <Global/Command>

#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

#include <QSqlDatabase>

JCommandManager::JCommandManager()
{
}

void JCommandManager::executeCommand(JID type,JID param1)
{
	switch(type){
	case ECT_Shutdown:
		shutdownMainServer();
		break;
	case ECT_Restart:
		restartMainServer();
		break;
	default:
		qDebug()<<"JCommandManager::executeCommand , no such type:"<<type<<" param is "<<param1;
	}
}

void JCommandManager::shutdownMainServer()
{
	QCoreApplication::exit(0);
}

void JCommandManager::restartMainServer()
{
	QCoreApplication::exit(0);
	QProcess::startDetached(QCoreApplication::applicationFilePath(),
							QStringList());
}
