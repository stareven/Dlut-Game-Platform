#ifndef MAGICNUMBER_H
#define MAGICNUMBER_H

/*
	* 以server端的名字命名。
*/

namespace MagicNumber
{
	enum EMagicNumber
	{
		EMN_Login,
		EMN_GetGameInfo,
		EMN_GetPort,
		EMN_UploadSubServer,
		EMN_DownloadGameClientFile,
		EMN_GetUserInfo,

		EMN_UserNumber=0x80,
	};

	typedef qint32 JMagicNumber;
}

#endif // MAGICNUMBER_H
