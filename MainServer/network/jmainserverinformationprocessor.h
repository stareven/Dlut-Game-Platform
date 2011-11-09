#ifndef JMAINSERVERINFORMATIONPROCESSOR_H
#define JMAINSERVERINFORMATIONPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

namespace NetworkData{
	class JHead;
}
class JMainServerInformationManager;

class JMainServerInformationProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JMainServerInformationProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	JType getProcessorType()const;

	void replyMtime(const NetworkData::JHead& head,JTime_t mtime);
	void replyData(const NetworkData::JHead& head,JTime_t currentTime,const QByteArray& data);
	void replyUploadResult(const NetworkData::JHead& head,JCode result);
protected:
	void processDownloadRemoteMtime(const NetworkData::JHead& head);
	void processDownloadData(const NetworkData::JHead& head);
	void processUploadData(const NetworkData::JHead& head,const QByteArray& uploadData);
private:
	JMainServerInformationManager& m_im;
};

#endif // JMAINSERVERINFORMATIONPROCESSOR_H
