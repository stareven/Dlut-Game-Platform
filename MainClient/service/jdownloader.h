#ifndef JDOWNLOADER_H
#define JDOWNLOADER_H

#include <Global/Global>

#include <QObject>
#include <QUrl>
#include <QNetworkReply>

class QFile;
class QNetworkAccessManager;

class JDownloader : public QObject
{
    Q_OBJECT
public:
    explicit JDownloader(QObject *parent = 0);
	~JDownloader();
	enum EDownloadState{
		EDS_Init,
		EDS_Begin,
		EDS_Downloading,
		EDS_Finished,
		EDS_Error,
	};

	void start(const QUrl& url,const QString& saveFilePath);
	void stop();

	EDownloadState getDownloadState()const;
signals:
	void begin();
	void rcvTotalSize(qint64 size);
	void progress(qint64,qint64);
	void finished();
	void error();
private:
	void start();
	bool makeSaveFileDir();
	bool openSaveFile();
	void beginGetDownloadTotalSize();
	void beginDownloadFile();
private slots:
	void on_headReply_finished();
	void on_reply_readyRead();
	void on_reply_finished();
	void on_reply_error(QNetworkReply::NetworkError);
	void on_reply_downloadProgress(qint64,qint64);
private:
	EDownloadState m_state;
	JCode m_error;
	QUrl m_url;
	QString m_saveFilePath;
	qint64 m_downloadTotalSize;
	QFile *m_file;
	QNetworkAccessManager* m_networkAccessManager;
	QNetworkReply* m_headReply;
	QNetworkReply* m_reply;
};

#endif // JDOWNLOADER_H
