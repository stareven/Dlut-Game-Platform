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

};

#endif // JSUBSERVERCONNECTION_H
