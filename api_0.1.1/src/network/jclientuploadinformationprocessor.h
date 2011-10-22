#ifndef JCLIENTUPLOADINFORMATIONPROCESSOR_H
#define JCLIENTUPLOADINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}

class JClientUploadInformationProcessor : public JClientNetworkDataProcessorBase
{
	Q_OBJECT
	explicit JClientUploadInformationProcessor(JClientSocketBase *socket = 0);
public:
	static JClientUploadInformationProcessor* getInstance();
	void sendInformationData(const NetworkData::JHead& head,const QByteArray& data);

	JType getProcessorType()const;
protected:
	void process(const QByteArray& data);
signals:
	void receiveSendInformationResult(const NetworkData::JHead& head,JCode result);
};

#endif // JCLIENTUPLOADINFORMATIONPROCESSOR_H
