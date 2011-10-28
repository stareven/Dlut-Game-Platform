#ifndef JREQUESTLOGINSOCKET_H
#define JREQUESTLOGINSOCKET_H

#include "jsocketbase.h"

class JRequestLoginSocket : public JSocketBase
{
Q_OBJECT
public:
    explicit JRequestLoginSocket(QObject *parent = 0);
    void login(const QString& loginname,const QString& passwd,const JID& role);
signals:
    void loginCode(const JCode& code);
private:
    JID m_userid;
    QByteArray m_loginhashcode;
public:
    JID getUserId()const;
    const QByteArray& getLoginHashCode()const;
protected:
	void dataProcess(const QByteArray&);
private:
	MagicNumber::JMagicNumber getMagicNumber()const
	{
		return MagicNumber::EMN_Login;
	}
};
#endif // JREQUESTLOGINSOCKET_H
