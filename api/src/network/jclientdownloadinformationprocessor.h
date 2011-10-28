#ifndef JCLIENTDOWNLOADINFORMATIONPROCESSOR_H
#define JCLIENTDOWNLOADINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}
class JClientDownloadInformationProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientDownloadInformationProcessor(JClientSocketBase *socket = 0);
public:
	static JClientDownloadInformationProcessor* getInstance();
	void requestInformationRemoteMtime(const NetworkData::JHead& head);
	void requestInformationData(const NetworkData::JHead& head);

	JType getProcessorType()const;
protected:
	void process(const QByteArray& data);
signals:
	void receiveRemoteMtime(const NetworkData::JHead& head,JTime_t remoteMtime);
	void receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray& data);
};

#endif // JCLIENTDOWNLOADINFORMATIONPROCESSOR_H
