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
	void start(const QString& gamename,
			   const JVersion& version,
			   QObject* parent,
			   const QHostAddress& address,
			   quint16 port);
private:
	bool download();
	bool run();
	QString getPath();

	QString m_gamename;
	JVersion m_version;
	QObject* m_parent;
	QHostAddress m_address;
	quint16 m_port;
};

#endif // JDOWNLOADRUN_H
