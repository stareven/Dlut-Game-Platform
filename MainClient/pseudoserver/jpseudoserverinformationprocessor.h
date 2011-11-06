#ifndef JPSEUDOSERVERINFORMATIONPROCESSOR_H
#define JPSEUDOSERVERINFORMATIONPROCESSOR_H

#include <Processor/JServerInformationProcessorBase>

class JPseudoServerInformationProcessor : public JServerInformationProcessorBase
{
    Q_OBJECT
public:
	explicit JPseudoServerInformationProcessor(JServerSocketBase *socket);
protected:
	void processDownloadRemoteMtime(const NetworkData::JHead& head);
	void processDownloadData(const NetworkData::JHead& head);
	void processUploadData(const NetworkData::JHead& head,const QByteArray& uploadData);
};

#endif // JPSEUDOSERVERINFORMATIONPROCESSOR_H
