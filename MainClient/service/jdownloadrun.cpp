#include "jdownloadrun.h"

#include <QProcess>
#include <QDebug>
#include <QString>
#include <QHostAddress>
#include <QFileInfo>

#include "network/jdownloadgamefilesocket.h"
#include "service/jcryprorecorder.h"

JDownloadRun::JDownloadRun()
{
}

void JDownloadRun::setGame(const QString& gamename,
			 const JVersion& version)
{
	m_gamename=gamename;
	m_version=version;
}

void JDownloadRun::setHost(EHostType hostType,const SHost& host)
{
	m_hosts[hostType]=host;
}

void JDownloadRun::setParent(QObject* parent)
{
	m_parent=parent;
}

bool JDownloadRun::needDownload()const
{
	QFileInfo fi(getPath());
	if(fi.exists())
	{
		return false;
	}
	return true;
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
	dgfs.connectToHost(m_hosts[EHT_Download].m_address,m_hosts[EHT_Download].m_port);
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
	QString path=getPath();
	static QProcess *s_process=NULL;
	if(s_process==NULL)
	{
		s_process=new QProcess(m_parent);
	}
	if(s_process->state()==QProcess::NotRunning)
	{
		qDebug()<<"run:"<<path;
		s_process->setProcessChannelMode(QProcess::ForwardedChannels);
		s_process->start(path,getArguments());
		return true;
	}else{
		qDebug()<<"is running.escape";
		return false;
	}
}

QString JDownloadRun::getPath()const
{
	return QString("./%1%2").arg(m_gamename).arg(m_version.getData()).replace(' ','_');
}

QStringList JDownloadRun::getArguments()const
{
	QStringList ret;
	JCryproRecorder cr;
	ret<<QString::number(cr.getUserId());
	ret<<cr.getCrypro().toHex().toUpper();
	ret<<m_hosts[EHT_MainServer].m_address.toString();
	ret<<QString::number(m_hosts[EHT_MainServer].m_port);
	ret<<m_hosts[EHT_GameServer].m_address.toString();
	ret<<QString::number(m_hosts[EHT_GameServer].m_port);
	return ret;
}
