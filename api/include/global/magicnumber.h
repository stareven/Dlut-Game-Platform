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
	};

	typedef qint32 JMagicNumber;

	inline JMagicNumber getMagicNumber(EMagicNumber mn)
	{
		JMagicNumber ret;
		ret=('D' << 24 ) |
			('G' << 16 ) |
			('P' <<  8 ) |
			mn;
		return ret;
	}
}

#endif // MAGICNUMBER_H
