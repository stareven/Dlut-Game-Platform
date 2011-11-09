#ifndef JSERVERNETWORKDATAPROCESSORBASE_H
#define JSERVERNETWORKDATAPROCESSORBASE_H

#include "jnetworkdataprocessorbase.h"

class JServerNetworkDataProcessorBase : public JNetworkDataProcessorBase
{
    Q_OBJECT
public:
	// 由JServerBase的子类作为工厂
	explicit JServerNetworkDataProcessorBase(JSession* session,JSocketBase *socket);
};

#endif // JSERVERNETWORKDATAPROCESSORBASE_H
