#ifndef JSUBSERVERCONNECTION_H
#define JSUBSERVERCONNECTION_H

#include "jplhconnectionbase.h"

class JSubServerConnection : public JPlhConnectionBase
{
    Q_OBJECT
public:
	explicit JSubServerConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void afterPlh(const QByteArray &);
private:
	JID m_subserverId;
protected:
	void on_socket_disconnected();
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UploadSubServer;
	}
};

#endif // JSUBSERVERCONNECTION_H
