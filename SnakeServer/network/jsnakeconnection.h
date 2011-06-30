#ifndef JSNAKECONNECTION_H
#define JSNAKECONNECTION_H

#include "network/jconnectionbase.h"

class JSnakeConnection : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JSnakeConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
};

#endif // JSNAKECONNECTION_H
