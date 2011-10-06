#ifndef JCLIENTINFORMATIONPROCESSOR_H
#define JCLIENTINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

namespace NetworkData{
	class JHead;
}
class JClientInformationProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
public:
    explicit JClientInformationProcessor(QObject *parent = 0);
	void requestInformationTime(const NetworkData::JHead& head);
	void requestInformationData(const NetworkData::JHead& head);
protected:
	void process(const QByteArray& data);
signals:
	void receiveLastModifyTime(const NetworkData::JHead& head,JTime_t time);
	void receiveData(const NetworkData::JHead& head,const QByteArray& data);
};

#endif // JCLIENTINFORMATIONPROCESSOR_H
