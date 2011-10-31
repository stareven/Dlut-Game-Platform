#ifndef JMAINSERVERDOWNLOADINFORMATIONPROCESSOR_H
#define JMAINSERVERDOWNLOADINFORMATIONPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

namespace NetworkData{
	class JHead;
}
class JMainServerInformationManager;

class JMainServerDownloadInformationProcessor : public JServerNetworkDataProcessorBase
{
	Q_OBJECT
public:
	JMainServerDownloadInformationProcessor(JServerSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;

	void sendInformationMtime(const NetworkData::JHead& head);
	void sendInformationData(const NetworkData::JHead& head);
private:
	JMainServerInformationManager& m_im;
};

#endif // JMAINSERVERDOWNLOADINFORMATIONPROCESSOR_H
