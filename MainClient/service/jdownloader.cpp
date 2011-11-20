#include "jdownloader.h"

#include <Global/CodeError>
#include <DataStruct/JElapsedTimer>

#include <QApplication>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

JDownloader::JDownloader(QObject *parent) :
    QObject(parent)
{
	m_state = EDS_Init;
	m_error = ESuccess;
	m_downloadTotalSize = -1;
	m_file = new QFile(this);
	m_networkAccessManager = new QNetworkAccessManager(this);
}

void JDownloader::start(const QUrl& url,const QString& saveFilePath)
{
	QFileInfo fileinfo(saveFilePath);
	qDebug()<<url<<fileinfo.absoluteDir().absolutePath();
	m_url = url;
	m_saveFilePath = saveFilePath;
	start();
}

JCode JDownloader::waitForFinished(int msecs)
{
	qDebug()<<__FUNCTION__<<msecs;
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(getDownloadState()!=EDS_Downloading)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_error;
}

void JDownloader::stop()
{
	return;
}

void JDownloader::start()
{
	m_state = EDS_Begin;
	if(!makeSaveFileDir()){
		m_state = EDS_Error;
		return;
	}
	if(!openSaveFile()){
		m_state = EDS_Error;
		return;
	}
	if(!getDownloadTotalSize()){
		m_state = EDS_Error;
		return;
	}
	beginDownloadFile();
}

JDownloader::EDownloadState JDownloader::getDownloadState()const
{
	return m_state;
}

bool JDownloader::makeSaveFileDir()
{
	QFileInfo fileinfo(m_saveFilePath);
	QString absoluteDir = fileinfo.absoluteDir().absolutePath();
	qDebug()<<m_url<<absoluteDir;
	QDir dir;
	bool result = dir.mkpath(absoluteDir);
	if(!result){
		qDebug()<<"make dir failed.";
		m_error = EMakeDirFailed;
	}
	return result;
}

bool JDownloader::openSaveFile()
{
	m_file->setFileName(m_saveFilePath);
	bool result = m_file->open(QIODevice::WriteOnly | QIODevice::Append);
	if(!result){
		qDebug()<<"open file failed : "<<m_file->errorString();
		m_error = EOpenFileFailed;
	}
	return result;
}

bool JDownloader::getDownloadTotalSize()
{
	QEventLoop e;
	QNetworkReply* pReply = m_networkAccessManager->head(QNetworkRequest(m_url));
	connect(pReply,SIGNAL(finished()),&e,SLOT(quit()));
	e.exec();
	QByteArray contentLength = "Content-Length";
	qDebug()<<__FUNCTION__
			<<pReply->rawHeaderList()
			<<pReply->rawHeader(contentLength);

	if(pReply->hasRawHeader(contentLength)){
		bool ok;
		m_downloadTotalSize = pReply->rawHeader(contentLength).toLongLong(&ok);
		Q_ASSERT (ok);
		m_error = ESuccess;
		return true;
	}else{
		m_error = ECannotGetContentLengthInHead;
		return false;
	}
	m_error = EUnknownError;
	return false;
}

void JDownloader::beginDownloadFile()
{
	qDebug()<<__FUNCTION__;
	if(m_file->size() < m_downloadTotalSize){
		QNetworkRequest request(m_url);
		QString range=QString("bytes=%1-%2")
					  .arg(m_file->size())
					  .arg(m_downloadTotalSize);
		request.setRawHeader("Range",range.toAscii());
		m_reply = m_networkAccessManager->get(request);
		connect(m_reply,SIGNAL(readyRead()),SLOT(on_reply_readyRead()));
		connect(m_reply,SIGNAL(finished()),SLOT(on_reply_finished()));
		connect(m_reply,
				SIGNAL(error(QNetworkReply::NetworkError)),
				SLOT(on_reply_error(QNetworkReply::NetworkError)));
		connect(m_reply,
				SIGNAL(downloadProgress(qint64,qint64)),
				SLOT(on_reply_downloadProgress(qint64,qint64)));
		m_state = EDS_Downloading;
		m_error = ESuccess;
	}else if(m_file->size() == m_downloadTotalSize){
		on_reply_finished();
	}else{
		qDebug()<<__FUNCTION__<<"file size larger than total size";
		m_file->close();
		m_file->remove();
		start();
	}
}

void JDownloader::on_reply_readyRead()
{
	qDebug()<<__FUNCTION__;
	Q_ASSERT(m_file != NULL && m_file->isWritable());
	m_file->write(m_reply->readAll());
}

void JDownloader::on_reply_finished()
{
	m_file->close();
	m_state = EDS_Finished;
}

void JDownloader::on_reply_error(QNetworkReply::NetworkError)
{
	qDebug()<<__FUNCTION__<<m_reply->errorString();
	m_state = EDS_Error;
}

void JDownloader::on_reply_downloadProgress(qint64 a,qint64 b)
{
	qDebug()<<"file size:"<<m_file->size()
			<<" total size:"<<m_downloadTotalSize
			<<" a="<<a
			<<" b="<<b;
}
