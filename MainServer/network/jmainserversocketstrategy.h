#ifndef JMAINSERVERSOCKETSTRATEGY_H
#define JMAINSERVERSOCKETSTRATEGY_H

#include <Socket/JSocketStrategy>

class JMainServerSocketStrategy : public JSocketStrategy
{
    Q_OBJECT
	explicit JMainServerSocketStrategy(QObject *parent = 0);
public:
	static JMainServerSocketStrategy* getInstance();
	bool filterBeforeProcess(JSocketBase* socket);
};

#endif // JMAINSERVERSOCKETSTRATEGY_H
