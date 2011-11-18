#ifndef JDOWNLOADER_H
#define JDOWNLOADER_H

#include <Global/Global>

#include <QObject>

class QUrl;

class JDownloader : public QObject
{
    Q_OBJECT
public:
    explicit JDownloader(QObject *parent = 0);
	void start(const QUrl& url,const QString& saveFilePath);
	JCode waitForFinished();
	void stop();
};

#endif // JDOWNLOADER_H
