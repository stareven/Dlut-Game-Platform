#ifndef JMAINCLIENTSOCKET_H
#define JMAINCLIENTSOCKET_H

#include "jclientsocketbase.h"

class JMainClientSocket : public JClientSocketBase
{
    Q_OBJECT
	explicit JMainClientSocket(QObject *parent = 0);
public:
	static JMainClientSocket* getInstance();
};

#endif // JMAINCLIENTSOCKET_H
