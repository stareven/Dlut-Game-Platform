#include "jdownloadrun.h"

#include <QProcess>
#include <QDebug>
#include <QString>
#include <QHostAddress>
#include <QFileInfo>

#include "network/jdownloadgamefilesocket.h"

JDownloadRun::JDownloadRun()
{
}

void JDownloadRun::start(const QString& gamename,
						 const JVersion& version,
						 QObject* parent,
						 const QHostAddress& address,
						 quint16 port)
{
	m_gamename=gamename;
	m_version=version;
	m_parent=parent;
	m_address=address;
	m_port=port;
	qDebug()<<"gamename:"<<m_gamename<<"address:"<<m_address.toString()<<"port:"<<m_port;
	if(!download())
	{
		qDebug()<<"download failed.";
		return;
	}
	if(!run())
	{
		qDebug()<<"run failed.";
		return;
	}
}

bool JDownloadRun::download()
{
	QFileInfo fi(getPath());
	if(fi.exists())
	{
		qDebug()<<"already exist.";
		return true;
	}
	JDownloadGameFileSocket dgfs;
	dgfs.connectToHost(m_address,m_port);
	if(!dgfs.waitForConnected(1000))
	{
		qDebug()<<"connect failed.";
		return false;
	}
	dgfs.rqsGameFile(m_gamename,m_version,getPath());
	return dgfs.waitForDownloaded();
}

bool JDownloadRun::run()
{
//	qDebug()<<"zan shi bu xiang run.";
//	return false;
	QString path=getPath();
	QProcess *process=new QProcess(m_parent);
	qDebug()<<"run:"<<path;
	process->setProcessChannelMode(QProcess::MergedChannels);
	process->start(path);
	process->waitForFinished();
	qDebug()<<process->errorString();
	return true;
}

QString JDownloadRun::getPath()
{
	return QString("./%1%2").arg(m_gamename).arg(m_version.getData()).replace(' ','_');
}
