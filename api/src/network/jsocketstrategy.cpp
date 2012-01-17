#include "jsocketstrategy.h"

/*!
    \class JSocketStrategy jsocketstrategy.h <Socket/JSocketStrategy>
    \ingroup socket
    \brief 套接字认证

    主要在 filterBeforeProcess() 方法
*/

JSocketStrategy::JSocketStrategy(QObject *parent) :
    QObject(parent)
{
}

/*!
    \brief 在 Process 前进行认证

    如果返回true ， 内容将会继续被 Processor 处理。\n
    否则会被丢弃。\n

    子类需要重写此方法来自定义认证规则。\n
    默认实现只返回true。
*/
bool JSocketStrategy::filterBeforeProcess(JSocketBase*)
{
	return true;
}
