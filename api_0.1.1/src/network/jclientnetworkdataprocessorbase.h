#ifndef JCLIENTNETWORKDATAPROCESSORBASE_H
#define JCLIENTNETWORKDATAPROCESSORBASE_H

#include "jnetworkdataprocessorbase.h"

class JClientSocketBase;

class JClientNetworkDataProcessorBase : public JNetworkDataProcessorBase
{
    Q_OBJECT
public:
    explicit JClientNetworkDataProcessorBase(QObject *parent = 0);
    void setSocket(JClientSocketBase*);
    JClientSocketBase* getSocket()const;
private:
    JClientSocketBase* m_socket;
};

#endif // JCLIENTNETWORKDATAPROCESSORBASE_H
