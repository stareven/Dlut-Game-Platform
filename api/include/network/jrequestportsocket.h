#ifndef JREQUESTPORTSOCKET_H
#define JREQUESTPORTSOCKET_H

#include "jsocketbase.h"
#include "global/eportsrv.h"

class JRequestPortSocket : public JSocketBase
{
    Q_OBJECT
public:
    explicit JRequestPortSocket(QObject *parent = 0);
    void sendLoginHashCode(JID,const QByteArray&);
    void rqsServerPort(EServerType);
protected:
    void dataProcess(const QByteArray&);
signals:
    void rcvLoginHashConfirm(bool);
    void rcvServerPort(quint16);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_GetPort;
	}
};

#endif // JREQUESTPORTSOCKET_H
