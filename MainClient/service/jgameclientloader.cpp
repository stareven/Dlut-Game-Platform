#include "jgameclientloader.h"
#include "jdownloader.h"

#include <Global/CodeError>
#include <Session/JSession>

#include <QProcess>
#include <QFile>

JGameClientLoader::JGameClientLoader()
{
	m_downloader = new JDownloader;
}

JGameClientLoader::~JGameClientLoader()
{
	delete m_downloader;
}

void JGameClientLoader::setParent(QObject* parent)
{
	m_parent = parent;
}

void JGameClientLoader::setPseudoServer(const SHost& pseudo)
{
	m_pseudoServer = pseudo;
}

void JGameClientLoader::setGameInfo(const JGameInfo& gameinfo)
{
	m_gameInfo = gameinfo;
}

void JGameClientLoader::setServerInfo(const JServerInfo& serverinfo)
{
	m_serverInfo = serverinfo;
}

void JGameClientLoader::setSession(JSession* session)
{
	m_session = session;
}

JDownloader* JGameClientLoader::getDownloader()const
{
	return m_downloader;
}

const QString& JGameClientLoader::getErrorString()const
{
	return m_error;
}

void JGameClientLoader::download()
{
	m_downloader->start(
				m_gameInfo.getDownloadUrl(),
				getSaveFilePath());
}

void JGameClientLoader::install()
{
	QFile file(getSaveFilePath());
	file.setPermissions(QFile::Permissions(0x7555));
}

void JGameClientLoader::start()
{
	static QProcess *s_process=NULL;
	if(s_process==NULL)
	{
		s_process=new QProcess(m_parent);
	}
	if(s_process->state()==QProcess::NotRunning)
	{
		qDebug()<<"run:"<<getSaveFilePath();
		s_process->setProcessChannelMode(QProcess::ForwardedChannels);
		s_process->start(getSaveFilePath(),getArguments());
		if(s_process->waitForStarted(1000)){
			qDebug()<<"run succeed";
		}else{
			qDebug()<<"run failed"<<s_process->errorString();
		}
	}else{
		qDebug()<<"is running.escape";
	}
}

void JGameClientLoader::setErrorString(const QString& error)
{
	m_error = error;
}

QString JGameClientLoader::getSaveFilePath()const
{
	return QString("%1/%2/%3")
			.arg(m_gameInfo.getAuthor())
			.arg(m_gameInfo.getName())
			.arg("setup");
}

QStringList JGameClientLoader::getArguments()const
{
	QStringList ret;
	ret<<QString::number(m_session->getUserId());
	ret<<m_session->getLoginHashCodeStr();
	ret<<m_pseudoServer.m_address.toString();
	ret<<QString::number(m_pseudoServer.m_port);
	ret<<m_serverInfo.getHost().m_address.toString();
	ret<<QString::number(m_serverInfo.getHost().m_port);
	return ret;
}
