#ifndef JSNAKESOCKET_H
#define JSNAKESOCKET_H

#include "network/jsocketbase.h"

class JSnakeSocket : public JSocketBase
{
    Q_OBJECT
public:
	explicit JSnakeSocket(QObject *parent = 0);
	void sendHello(JID userId);
	void sendRqsUserlist();
signals:
	void rcvHello(JCode code);
	void rcvUserlist(JID roomId,const QList<JID>& userlist);
protected:
	void dataProcess(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_UserNumber+1;
	}
};

#endif // JSNAKESOCKET_H
