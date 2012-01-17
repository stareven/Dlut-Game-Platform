#ifndef JSOCKETSTRATEGY_H
#define JSOCKETSTRATEGY_H

#include <QObject>

class JSocketBase;

/*!
    \file jsocketstrategy.h
    \ingroup socket
    \brief 定义了 JSocketStrategy 类
*/

class JSocketStrategy : public QObject
{
    Q_OBJECT
public:
    explicit JSocketStrategy(QObject *parent = 0);
	virtual bool filterBeforeProcess(JSocketBase* socket);
};

#endif // JSOCKETSTRATEGY_H
