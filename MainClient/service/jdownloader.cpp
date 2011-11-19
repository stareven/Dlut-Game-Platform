#include "jdownloader.h"

#include <Global/CodeError>
#include <DataStruct/JElapsedTimer>

#include <QApplication>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

JDownloader::JDownloader(QObject *parent) :
    QObject(parent)
{
	m_state = EDS_Init;
	m_error = ESuccess;
	m_downloadTotalSize = -1;
	m_file = new QFile(this);
}

void JDownloader::start(const QUrl& url,const QString& saveFilePath)
{
	QFileInfo fileinfo(saveFilePath);
	qDebug()<<url<<fileinfo.absoluteDir();
	m_url = url;
	m_saveFilePath = saveFilePath;
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
	m_error = EDeveloping;
	return false;
}

void JDownloader::beginDownloadFile()
{
	m_state = EDS_Error;
	m_error = EDeveloping;
}
