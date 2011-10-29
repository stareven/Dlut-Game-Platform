#ifndef JSERVERNETWORKDATAPROCESSORBASE_H
#define JSERVERNETWORKDATAPROCESSORBASE_H

#include "jnetworkdataprocessorbase.h"

class JServerSocketBase;

class JServerNetworkDataProcessorBase : public JNetworkDataProcessorBase
{
    Q_OBJECT
public:
	// 由JServerBase的子类作为工厂
	explicit JServerNetworkDataProcessorBase(JServerSocketBase *socket);
protected:
	void sendData(const QByteArray& data);
private:
	JServerSocketBase* const m_socket;
};

#endif // JSERVERNETWORKDATAPROCESSORBASE_H
