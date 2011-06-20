#ifndef JDOWNLOADRUN_H
#define JDOWNLOADRUN_H

#include <QtGlobal>

#include <QString>
#include <QHostAddress>

class QObject;

class JDownloadRun
{
public:
    JDownloadRun();
	void start(const QString& gamename,
			   QObject* parent,
			   const QHostAddress& address,
			   quint16 port);
private:
	void download();
	void run();
	QString getPath();

	QString m_gamename;
	QObject* m_parent;
	QHostAddress m_address;
	quint16 m_port;
};

#endif // JDOWNLOADRUN_H
