#ifndef JSNAKESERVER_H
#define JSNAKESERVER_H

#include "network/jserverbase.h"

class JSnakeServer : public JServerBase
{
    Q_OBJECT
public:
    explicit JSnakeServer(QObject *parent = 0);
protected:
	JConnectionBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JSNAKESERVER_H
