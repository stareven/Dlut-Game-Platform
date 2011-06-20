#include "jdownloadrun.h"

#include <QProcess>
#include <QDebug>
#include <QString>
#include <QHostAddress>

JDownloadRun::JDownloadRun()
{
}

void JDownloadRun::start(const QString& gamename,
						 QObject* parent,
						 const QHostAddress& address,
						 quint16 port)
{
	m_gamename=gamename;
	m_parent=parent;
	m_address=address;
	m_port=port;
	download();
	run();
}

void JDownloadRun::download()
{
	qDebug()<<"JDownloadRun::download"<<m_gamename;
}

void JDownloadRun::run()
{
	QString path=getPath();
	QProcess *process=new QProcess(m_parent);
	process->start(path);
}

QString JDownloadRun::getPath()
{
	qDebug()<<"unfinished : JDownloadRun::name2Path"<<m_gamename;
	return QString("../SnakeClient-build-desktop/SnakeClient");
}
