#include "jinformation.h"

using namespace NetworkData;

/*!
    \class NetworkData::JInformation jinformation.h Information/JInformation
    \ingroup global
    \brief 以二进制格式保存数据内容
    
    将信息的内容序列化为二进制后保存，\n
    或取出二进制后反序列化为信息内容。
*/

/*!
    \namespace NetworkData
    \ingroup global
    \brief 网络数据相关
*/

/*!
    \enum EInformationProtocol
    \brief NetworkData 数据传输协议
*/

/*!
    \var EInformationProtocol EIP_DownloadRemoteMtime
    \brief 请求服务器端信息的最后修改时间
*/

/*!
    \var EInformationProtocol EIP_DownloadData
    \brief 请求服务器端信息
*/

/*!
    \var EInformationProtocol EIP_UploadData
    \brief 请求向服务器上传数据
*/

/*!
    \brief 构造函数
    
    \a head 是此信息的头信息。
*/
JInformation::JInformation(const JHead& head)
	:m_head(head)
{
	m_remoteMtime=0;
	m_localMtime=0;
}

/*!
    \brief 记录服务器端最后修改时间
*/
JCode JInformation::setRemoteMtime(JTime_t time)
{
	m_remoteMtime = time;
	return 0;
}

/*!
    \brief 设置本地最后修改时间
    
    本地时间可能与服务器端不同步，因此需要从服务器获取当前时间。
*/
JCode JInformation::setLocalMtime(JTime_t time)
{
	m_localMtime = time;
	return 0;
}

/*!
    \brief 以二进制格式保存数据内容
*/
JCode JInformation::setData(const QByteArray& data)
{
	m_data = data;
	return 0;
}

/*!
    \brief 返回服务器端最后修改时间
*/
JTime_t JInformation::getRemoteMtime()const
{
	return m_remoteMtime;
}

/*!
    \brief 返回本地最后修改时间
*/
JTime_t JInformation::getLocalMtime()const
{
	return m_localMtime;
}

/*!
    \brief 以二进制格式返回数据内容
*/
const QByteArray& JInformation::getData()const
{
	return m_data;
}
