#ifndef JCLIENTLOGINPROCESSOR_H
#define JCLIENTLOGINPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"
#include "../global/elogin.h"

class JClientLoginProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
private:
    explicit JClientLoginProcessor(QObject *parent = 0);
public:
    static JClientLoginProcessor* getInstance();
    void login(const QString& loginname,const QString& passwd,ERole role);
    JID getUserId()const;
signals:
    void loginCode(JCode);
protected:
    void process(const QByteArray& data);
	JType getProcessorType()const;
private:
    JID m_userid;
};

#endif // JCLIENTLOGINPROCESSOR_H
