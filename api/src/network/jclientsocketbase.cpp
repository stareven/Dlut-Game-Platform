#include "jclientsocketbase.h"

/*!
	\class JClientSocketBase jclientsocketbase.h <Socket/JClientSocketBase>
	\ingroup socket
	\brief 客户端套接字基类
	
	子类需要提供静态单例方法。
*/

/*!
	\brief 构造函数
	
	protected ，外部只能从静态单例方法获得此类或其子类对象。
*/
JClientSocketBase::JClientSocketBase(QTcpSocket* const socket,QObject *parent) :
	JSocketBase(socket,parent)
{
}
