#ifndef JSERVERINFORMATIONPROCESSORBASE_H
#define JSERVERINFORMATIONPROCESSORBASE_H

#include "jservernetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}

class JServerInformationProcessorBase : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JServerInformationProcessorBase(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;

	void replyMtime(const NetworkData::JHead& head,JTime_t mtime);
	void replyData(const NetworkData::JHead& head,JTime_t currentTime,const QByteArray& data);
	void replyUploadResult(const NetworkData::JHead& head,JCode result);
protected:
	virtual void processDownloadRemoteMtime(const NetworkData::JHead& head)=0;
	virtual void processDownloadData(const NetworkData::JHead& head)=0;
	virtual void processUploadData(const NetworkData::JHead& head,const QByteArray& uploadData)=0;
};

#endif // JSERVERINFORMATIONPROCESSORBASE_H
