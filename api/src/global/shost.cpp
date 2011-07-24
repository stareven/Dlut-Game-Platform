#include "global/shost.h"

/*!
	\class SHost
	
	\brief 记录一个地址和端口。
*/

/*!
	创建一个SHost。设置地址为\a address ，端口为\a port 。
	*/
SHost::SHost(const QHostAddress& address,quint16 port)
{
	m_address=address;
	m_port=port;
}

/*!
	判断是否为空。
	*/
bool SHost::isNull()const
{
	return m_address.isNull() || 0==m_port;
}
