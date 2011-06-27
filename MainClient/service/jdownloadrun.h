#ifndef JDOWNLOADRUN_H
#define JDOWNLOADRUN_H

#include <QtGlobal>

#include <QString>
#include <QHostAddress>

#include "global/jversion.h"

class QObject;

class JDownloadRun
{
public:
    JDownloadRun();
	void setGame(const QString& gamename,
				 const JVersion& version);
	void setHost(const QHostAddress& address,
				 quint16 port);
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

	QString m_gamename;
	JVersion m_version;
	QObject* m_parent;
	QHostAddress m_address;
	quint16 m_port;
};

#endif // JDOWNLOADRUN_H
