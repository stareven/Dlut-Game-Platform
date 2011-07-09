#ifndef JDOWNLOADRUN_H
#define JDOWNLOADRUN_H

#include <QString>

#include "global/jversion.h"
#include "global/shost.h"

class QObject;
class QProcess;

class JDownloadRun
{
public:
    JDownloadRun();
	void setGame(const QString& gamename,
				 const JVersion& version);
	enum EHostType{EHT_Download,EHT_MainServer,EHT_GameServer,EHT_Max};
	void setHost(EHostType hostType,const SHost&);
//	void setHost(const QHostAddress& address,quint16 port);
	void setParent(QObject* parent);
	bool needDownload()const;
	bool download();
	bool run();
//	void start(const QString& gamename,
//			   const JVersion& version,
//			   QObject* parent,
//			   const QHostAddress& address,
//			   quint16 port);
private:
	QString getPath()const;
	QStringList getArguments()const;

	QString m_gamename;
	JVersion m_version;
	QObject* m_parent;

	SHost m_hosts[EHT_Max];

	static QProcess* s_process;
};

#endif // JDOWNLOADRUN_H
