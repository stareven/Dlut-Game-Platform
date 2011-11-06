#ifndef JPSEUDOSERVER_H
#define JPSEUDOSERVER_H

#include <Socket/JServerBase>

class JPseudoServer : public JServerBase
{
    Q_OBJECT
public:
    explicit JPseudoServer(QObject *parent = 0);
protected:
	JServerSocketBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JPSEUDOSERVER_H
