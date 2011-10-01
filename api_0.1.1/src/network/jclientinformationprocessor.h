#ifndef JCLIENTINFORMATIONPROCESSOR_H
#define JCLIENTINFORMATIONPROCESSOR_H

#include "jclientnetworkdataprocessorbase.h"

class JClientInformationProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
public:
    explicit JClientInformationProcessor(QObject *parent = 0);
	void requestInformationTime(qint32 head);
	void requestInformationData(qint32 head);
protected:
	void process(const QByteArray& data);
signals:
	void receiveLastModifyTime(qint32 head,JTime_t time);
	void receiveData(qint32 head,const QByteArray& data);
};

#endif // JCLIENTINFORMATIONPROCESSOR_H
