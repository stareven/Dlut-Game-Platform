#ifndef JSNAKECONNECTION_H
#define JSNAKECONNECTION_H

#include "network/jconnectionbase.h"

class JRoomManager;

class JSnakeConnection : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JSnakeConnection(QTcpSocket* socket,QObject *parent = 0);
protected:
	void dataProcess(const QByteArray&);
	void on_socket_disconnected();
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
private:
	JRoomManager* m_roomMng;
private slots:
	void sendRoominfoUpdate(JID roomId);
	void sendRoominfoAdd(JID roomId);
	void sendRoominfoDelete(JID roomId);
};

#endif // JSNAKECONNECTION_H
