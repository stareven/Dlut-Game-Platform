#ifndef JSNAKESOCKET_H
#define JSNAKESOCKET_H

#include <Socket/JClientSocketBase>



class JSnakeSocket : public JClientSocketBase
{
    Q_OBJECT
	explicit JSnakeSocket(QObject *parent = 0);
public:
	static JSnakeSocket* getInstance();
};

#endif // JSNAKESOCKET_H
