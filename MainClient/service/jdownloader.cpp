#include "jdownloader.h"

#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

JDownloader::JDownloader(QObject *parent) :
    QObject(parent)
{
}

void JDownloader::start(const QUrl& url,const QString& saveFilePath)
{
	QFileInfo fileinfo(saveFilePath);
	qDebug()<<url<<fileinfo.absoluteDir();
}

JCode JDownloader::waitForFinished(int msecs)
{
	qDebug()<<__FUNCTION__<<msecs;
	return 1;
}

void JDownloader::stop()
{
	return;
}
