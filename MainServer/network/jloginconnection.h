#ifndef JLOGINCONNECTION_H
#define JLOGINCONNECTION_H

#include "network/jconnectionbase.h"

class JLoginConnection : public JConnectionBase
{
Q_OBJECT
public:
    explicit JLoginConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray&);
	void on_socket_disconnected();
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_Login;
	}
};

#endif // JLOGINCONNECTION_H
