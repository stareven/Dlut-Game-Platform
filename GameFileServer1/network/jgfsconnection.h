#ifndef JGFSCONNECTION_H
#define JGFSCONNECTION_H

#include "jconnectionbase.h"

class JGfsConnection : public JConnectionBase
{
    Q_OBJECT
public:
	explicit JGfsConnection(QTcpSocket* socket,QObject *parent = 0);

signals:

public slots:

};

#endif // JGFSCONNECTION_H
