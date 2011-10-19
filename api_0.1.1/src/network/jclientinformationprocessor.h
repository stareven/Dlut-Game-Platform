#ifndef JCLIENTINFORMATIONPROCESSOR_H
#define JCLIENTINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}
class JClientInformationProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientInformationProcessor(JClientSocketBase *socket = 0);
public:
	static JClientInformationProcessor* getInstance();
	void requestInformationRemoteMtime(const NetworkData::JHead& head);
	void requestInformationData(const NetworkData::JHead& head);

	JType getProcessorType()const;
protected:
	void process(const QByteArray& data);
signals:
	void receiveRemoteMtime(const NetworkData::JHead& head,JTime_t remoteMtime);
	void receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray& data);
};

#endif // JCLIENTINFORMATIONPROCESSOR_H
