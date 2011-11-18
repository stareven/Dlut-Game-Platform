#include "jgameclientloader.h"
#include "jdownloader.h"

#include <Global/CodeError>

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

JDownloader* JGameClientLoader::getDownloader()const
{
	return m_downloader;
}

JCode JGameClientLoader::load()
{
	JCode rtn;
	rtn = download();
	if(ESuccess != rtn){
		return rtn;
	}
	rtn = install();
	if(ESuccess != rtn){
		return rtn;
	}
	rtn = start();
	if(ESuccess != rtn){
		return rtn;
	}
	return ESuccess;
}

const QString& JGameClientLoader::getErrorString()const
{
	return m_error;
}

JCode JGameClientLoader::download()
{
	m_downloader->start(
				m_gameInfo.getDownloadUrl(),
				getSaveFilePath());
	return m_downloader->waitForFinished();
}

JCode JGameClientLoader::install()
{
	extern JCode asdf;
	return asdf;
}

JCode JGameClientLoader::start()
{
	extern JCode asdf;
	return asdf;
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
