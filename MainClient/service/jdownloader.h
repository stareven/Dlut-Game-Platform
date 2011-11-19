#ifndef JDOWNLOADER_H
#define JDOWNLOADER_H

#include <Global/Global>

#include <QObject>
#include <QUrl>

class QFile;

class JDownloader : public QObject
{
    Q_OBJECT
public:
    explicit JDownloader(QObject *parent = 0);
	enum EDownloadState{
		EDS_Init,
		EDS_Begin,
		EDS_Downloading,
		EDS_Finished,
		EDS_Error,
	};

	void start(const QUrl& url,const QString& saveFilePath);
	JCode waitForFinished(int msecs=60*60*1000);
	void stop();

	EDownloadState getDownloadState()const;
private:
	bool makeSaveFileDir();
	bool openSaveFile();
	bool getDownloadTotalSize();
	void beginDownloadFile();
private:
	EDownloadState m_state;
	JCode m_error;
	QUrl m_url;
	QString m_saveFilePath;
	qint64 m_downloadTotalSize;
	QFile *m_file;
};

#endif // JDOWNLOADER_H
