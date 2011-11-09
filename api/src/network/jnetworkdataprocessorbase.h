#ifndef JNETWORKDATAPROCESSORBASE_H
#define JNETWORKDATAPROCESSORBASE_H

#include <QObject>

#include "../global/jglobal.h"

class QByteArray;

class JSession;
class JSocketBase;

class JNetworkDataProcessorBase : public QObject
{
    Q_OBJECT
public:
	JNetworkDataProcessorBase (JSession* session,JSocketBase *socket);
    virtual void process(const QByteArray& data)=0;
	virtual JType getProcessorType()const=0;

	enum EProcessorType{
        EPI_LOGIN,
		EPI_INFORMATION,
		EPI_COMMAND,
    };

protected:
	JCode sendData(const QByteArray& data);
	JSession* getSession()const;
private:
	JSocketBase* m_socket;
	JSession* m_session;
};

#endif // JNETWORKDATAPROCESSORBASE_H
