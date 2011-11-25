#ifndef JENCRYPTOR_H
#define JENCRYPTOR_H

#include <QString>

class JEncryptor
{
public:
    JEncryptor();
	QString encryptPassword(const QString& pswd)const;
};

#endif // JENCRYPTOR_H
