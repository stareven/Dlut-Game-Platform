#ifndef JPSEUDOSERVER_H
#define JPSEUDOSERVER_H

#include <Socket/JServerBase>

class JPseudoServer : public JServerBase
{
    Q_OBJECT
	explicit JPseudoServer(QObject *parent = 0);
public:
	static JPseudoServer* getInstance();
protected:
	JServerSocketBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JPSEUDOSERVER_H
