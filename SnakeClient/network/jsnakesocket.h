#ifndef JSNAKESOCKET_H
#define JSNAKESOCKET_H

#include "network/jsocketbase.h"

namespace Snake
{
	class JRoom;
}

class JSnakeSocket : public JSocketBase
{
    Q_OBJECT
	explicit JSnakeSocket(QObject *parent = 0);
	static JSnakeSocket s_socket;
public:
	static JSnakeSocket& getInstance();
	void sendHello(JID userId);
	void sendRqsUserlist();
	void sendAddRoom(const Snake::JRoom&);
signals:
	void rcvHello(JCode code);
	void rcvUserlist(JID roomId,const QList<JID>& userlist);
	void rcvAddRoom(const Snake::JRoom&);
protected:
	void dataProcess(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
};

#endif // JSNAKESOCKET_H
