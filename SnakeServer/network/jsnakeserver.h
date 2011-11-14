#ifndef JSNAKESERVER_H
#define JSNAKESERVER_H

#include <Socket/JServerBase>

class JSnakeServer : public JServerBase
{
    Q_OBJECT
public:
    explicit JSnakeServer(QObject *parent = 0);
protected:
	JServerSocketBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JSNAKESERVER_H
