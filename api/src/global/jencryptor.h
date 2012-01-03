#ifndef JENCRYPTOR_H
#define JENCRYPTOR_H

#include <QString>

/*!
	\file jencryptor.h
	\ingroup global
	\brief 定义了 JEncryptor 类。
*/

class JEncryptor
{
public:
	QString encryptPassword(const QString& pswd)const;
};

#endif // JENCRYPTOR_H
