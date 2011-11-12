#ifndef JSOCKETSTRATEGY_H
#define JSOCKETSTRATEGY_H

#include <QObject>

class JSocketBase;

class JSocketStrategy : public QObject
{
    Q_OBJECT
public:
    explicit JSocketStrategy(QObject *parent = 0);
	virtual bool filterBeforeProcess(JSocketBase* socket);
};

#endif // JSOCKETSTRATEGY_H
