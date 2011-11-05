#ifndef JSERVERNETWORKDATAPROCESSORBASE_H
#define JSERVERNETWORKDATAPROCESSORBASE_H

#include "jnetworkdataprocessorbase.h"

class JServerSocketBase;
class JSession;

class JServerNetworkDataProcessorBase : public JNetworkDataProcessorBase
{
    Q_OBJECT
public:
	// 由JServerBase的子类作为工厂
	explicit JServerNetworkDataProcessorBase(JSession* session,JServerSocketBase *socket);
protected:
	void sendData(const QByteArray& data);
private:
	JServerSocketBase* const m_socket;
	JSession* m_session;
protected:
	JSession* getSession()const;
};

#endif // JSERVERNETWORKDATAPROCESSORBASE_H
