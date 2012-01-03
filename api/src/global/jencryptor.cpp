#include "jencryptor.h"

#include <QCryptographicHash>

/*!
	\class JEncryptor
	\ingroup global
	\brief 密码加密
	
	密码加密方法可能会有改动，因此独立成一个类。
*/

/*!
    \brief 将密码 \a pswd 加密
    
    目前直接使用MD5加密。
*/
QString JEncryptor::encryptPassword(const QString& pswd)const
{
	QCryptographicHash ch(QCryptographicHash::Md5);
	ch.addData(pswd.toAscii());
	return ch.result().toHex().toUpper();
}
