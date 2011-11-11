#ifndef JUSERREGISTER_H
#define JUSERREGISTER_H

#include <Global/Global>

#include <QString>

class JUserRegister
{
public:
    JUserRegister();
	void execute(const QString& loginname,const QString& password);
	JCode getResult()const;
	JID getUserId()const;
	const QString& getLoginname()const;
private:
	JCode m_result;
	JID m_userId;
	QString m_loginname;
};

#endif // JUSERREGISTER_H
