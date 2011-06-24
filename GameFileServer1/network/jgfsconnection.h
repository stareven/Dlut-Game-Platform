#ifndef JGFSCONNECTION_H
#define JGFSCONNECTION_H

#include "network/jconnectionbase.h"

class JGfsConnection : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JGfsConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray &);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_DownloadGameClientFile;
	}
};

#endif // JGFSCONNECTION_H
