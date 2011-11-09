#ifndef JCLIENTINFORMATIONPROCESSOR_H
#define JCLIENTINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}

class JClientInformationProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JClientInformationProcessor(JSession* session,JSocketBase *socket);
public:
	static JClientInformationProcessor* getInstance();
	void requestDownloadRemoteMtime(const NetworkData::JHead& head);
	void requestDownloadData(const NetworkData::JHead& head);
	void requestUploadData(const NetworkData::JHead& head,const QByteArray& data);

	JType getProcessorType()const;
protected:
	void process(const QByteArray& data);
signals:
	void receiveRemoteMtime(const NetworkData::JHead& head,JTime_t remoteMtime);
	void receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray& data);
	void receiveUploadResult(const NetworkData::JHead& head,JCode result);
};

#endif // JCLIENTINFORMATIONPROCESSOR_H
