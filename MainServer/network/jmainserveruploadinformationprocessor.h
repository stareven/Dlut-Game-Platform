#ifndef JMAINSERVERUPLOADINFORMATIONPROCESSOR_H
#define JMAINSERVERUPLOADINFORMATIONPROCESSOR_H

#include "Processor/JServerNetworkDataProcessorBase"

namespace NetworkData{
	class JHead;
}
class JMainServerInformationManager;

class JMainServerUploadInformationProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerUploadInformationProcessor(JServerSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;

	void sendUploadResult(const NetworkData::JHead& head,JCode result);
private:
	JMainServerInformationManager& m_im;
};

#endif // JMAINSERVERUPLOADINFORMATIONPROCESSOR_H
