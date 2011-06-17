#include "jdownloadrun.h"

#include <QProcess>
#include <QDebug>

JDownloadRun::JDownloadRun()
{
}

void JDownloadRun::start(const QString& gamename,QObject* parent)
{
	download(gamename);
	run(gamename,parent);
}

void JDownloadRun::download(const QString& gamename)
{
	qDebug()<<"JDownloadRun::download"<<gamename;
}

void JDownloadRun::run(const QString& gamename,QObject* parent)
{
	QString path=name2Path(gamename);
	QProcess *process=new QProcess(parent);
	process->start(path);
}

QString JDownloadRun::name2Path(const QString& gamename)
{
	qDebug()<<"unfinished : JDownloadRun::name2Path"<<gamename;
	return QString("../SnakeClient-build-desktop/SnakeClient");
}
