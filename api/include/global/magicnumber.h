#ifndef MAGICNUMBER_H
#define MAGICNUMBER_H

/*!
	\brief 定义网络通信的“魔数”。

	网络通信需要确定是不是同一个协议。\n
	在每个数据包的开头是魔数和数据长度，之后才是数据的内容。\n

	\sa JSocketBase::sendData() JSocketBase::on_socket_readyRead()
*/
namespace MagicNumber
{
	/*!
		各种协议的魔数值。
	*/
	enum EMagicNumber
	{
		EMN_Login,
		EMN_GetGameInfo,
		EMN_GetPort,
		EMN_UploadSubServer,
		EMN_DownloadGameClientFile,
		EMN_GetUserInfo,

		EMN_UserNumber=0x80,/**<  用户自定义协议的魔数需要大于EMN_UserNumber的值。 */
	};

	/*!
		统一网络通信格式，将魔数定义为32位带符号整数。
	*/
	typedef qint32 JMagicNumber;
}

#endif // MAGICNUMBER_H
