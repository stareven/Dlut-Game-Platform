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
};

#endif // JCLIENTINFORMATIONPROCESSOR_H
