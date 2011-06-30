#ifndef JGFSSERVER_H
#define JGFSSERVER_H

#include "network/jserverbase.h"

class JGfsServer : public JServerBase
{
    Q_OBJECT
public:
    explicit JGfsServer(QObject *parent = 0);
protected:
	JConnectionBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JGFSSERVER_H
