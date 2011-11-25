#include "jencryptor.h"

#include <QCryptographicHash>

JEncryptor::JEncryptor()
{
}

QString JEncryptor::encryptPassword(const QString& pswd)const
{
	QCryptographicHash ch(QCryptographicHash::Md5);
	ch.addData(pswd.toAscii());
	return ch.result().toHex().toUpper();
}
