#ifndef JCLIENTNETWORKDATAPROCESSORBASE_H
#define JCLIENTNETWORKDATAPROCESSORBASE_H

#include "jnetworkdataprocessorbase.h"

class JClientSocketBase;

/*!
	在子类中提供单例方法，并在单例方法中配置Processor（如socket等）。
	static JxxxProcessor* getInstance();
*/
class JClientNetworkDataProcessorBase : public JNetworkDataProcessorBase
{
    Q_OBJECT
protected:
    explicit JClientNetworkDataProcessorBase(QObject *parent = 0);
public:
    void setSocket(JClientSocketBase*);
    JClientSocketBase* getSocket()const;
private:
    JClientSocketBase* m_socket;
};

#endif // JCLIENTNETWORKDATAPROCESSORBASE_H
