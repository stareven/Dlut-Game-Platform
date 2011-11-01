#ifndef JDOWNLOADGAMEFILESOCKET_H
#define JDOWNLOADGAMEFILESOCKET_H

#include "network/jsocketbase.h"

#include "global/jversion.h"

class QFile;

class JDownloadGameFileSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JDownloadGameFileSocket(QObject *parent = 0);
	void rqsGameFile(const QString& gamename,const JVersion& version,const QString& path);
	bool waitForConnected( int msecs = 30000 );
	bool waitForDownloaded(int msecs = 0x7fffffff);
protected:
	void dataProcess(const QByteArray &);
private:
	struct SHead{
		bool m_isReceived;
		QString m_gamename;
		JVersion m_version;
		qint64 m_size;
		qint64 m_pieceSize;
		qint64 m_nTotal;
		qint64 m_nNow;
	};
	SHead m_head;
	QString m_path;
	QFile *m_file;
	bool m_isError;
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_DownloadGameClientFile;
	}
};

#endif // JDOWNLOADGAMEFILESOCKET_H
