#ifndef JGAMECLIENTLOADER_H
#define JGAMECLIENTLOADER_H

#include <DataStruct/SHost>
#include <DataStruct/JGameInfo>
#include <DataStruct/JServerInfo>

class JDownloader;

class JGameClientLoader
{
public:
    JGameClientLoader();
	~JGameClientLoader();
	void setParent(QObject* parent);
	void setPseudoServer(const SHost& pseudo);
	void setGameInfo(const JGameInfo& gameinfo);
	void setServerInfo(const JServerInfo& serverinfo);

	JDownloader* getDownloader()const;
	JCode load();
	const QString& getErrorString()const;
private:
	JCode download();
	JCode install();
	JCode start();
private:
	void setErrorString(const QString& error);
	QString getSaveFilePath()const;
private:
	SHost m_pseudoServer;
	JGameInfo m_gameInfo;
	JServerInfo m_serverInfo;
	JDownloader* m_downloader;
	QObject* m_parent;
	QString m_error;
};

#endif // JGAMECLIENTLOADER_H
