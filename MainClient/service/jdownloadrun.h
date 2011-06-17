#ifndef JDOWNLOADRUN_H
#define JDOWNLOADRUN_H

class QString;
class QObject;

class JDownloadRun
{
public:
    JDownloadRun();
	void start(const QString& gamename,QObject* parent);
private:
	void download(const QString& gamename);
	void run(const QString& gamename,QObject* parent);
	QString name2Path(const QString& gamename);
};

#endif // JDOWNLOADRUN_H
