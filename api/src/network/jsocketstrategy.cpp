#include "jsocketstrategy.h"

JSocketStrategy::JSocketStrategy(QObject *parent) :
    QObject(parent)
{
}

bool JSocketStrategy::filterBeforeProcess(JSocketBase*)
{
	return true;
}
