#ifndef MAGICNUMBER_H
#define MAGICNUMBER_H

/*!
	\file magicnumber.h
	\brief 定义了 MagicNumber 命名空间
*/

/*!
	\ingroup global
	\brief 定义网络通信的“魔数”。
	

	网络通信需要确定是不是同一个协议。\n
	在每个数据包的开头是魔数和数据长度，之后才是数据的内容。\n

	\sa JSocketBase
*/
namespace MagicNumber
{
	/*!
		\brief 各种协议的魔数值。
	*/
	enum EMagicNumber
	{
		EMN_Login,///< 登录协议
		EMN_GetGameInfo,///< 获取游戏信息协议
		EMN_GetPort,///< 获取端口列表协议
		EMN_UploadSubServer,///< 上传 SubServer 相关信息协议
		EMN_DownloadGameClientFile,///< 下载游戏客户端协议
		EMN_GetUserInfo,///< 获取玩家信息协议

		EMN_UserNumber=0x80,/**<  用户自定义协议的魔数需要大于EMN_UserNumber的值。 */
	};

	/*!
		\brief “魔数”的定义。

		统一网络通信格式，将魔数定义为32位带符号整数。
	*/
	typedef qint32 JMagicNumber;
}

#endif // MAGICNUMBER_H
