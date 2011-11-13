#ifndef JREQUESTUSERREGISTER_H
#define JREQUESTUSERREGISTER_H

#include "jrequestbase.h"
#include "../global/jglobal.h"
#include "../global/eregister.h"

class JClientUserRegisterProcessor;

class JRequestUserRegister : public JRequestBase
{
    Q_OBJECT
public:
    explicit JRequestUserRegister(QObject *parent = 0);
	void sendRegister(const QString& loginname,const QString& password);
	/// \brief 注册状态
	enum ERegisterState{
		ERS_Init, ///< 初始状态
		ERS_Sending, ///< 正在发送注册请求
		ERS_Success, ///< 注册成功
		ERS_Failed, ///< 注册失败
	};
	ERegisterState getRegisterState()const;
	bool waitForRegisterResult(int msecs=30000);
	const QString& getRegisterError()const;
signals:
	void receiveRegisterResult(JCode result,JID userId,const QString& loginname);
protected slots:
	void on_processor_receiveRegisterResult(JCode result,JID userId,const QString& loginname);
private:
	ERegisterState m_state;
	ERegister m_registerError;
	JClientUserRegisterProcessor *m_processor;
};

#endif // JREQUESTUSERREGISTER_H
