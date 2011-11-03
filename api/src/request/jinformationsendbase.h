#ifndef JINFORMATIONSENDBASE_H
#define JINFORMATIONSENDBASE_H

#include "../network/jinformation.h"
#include <QMap>

#include "jrequestbase.h"

class JClientInformationProcessor;

class JInformationSendBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JInformationSendBase(QObject *parent = 0);
	void sendInformationData(const NetworkData::JHead& head,const QByteArray& data);
	bool waitForSendResult(const NetworkData::JHead& head,int msecs=30000);
	JCode getSendResult(const NetworkData::JHead& head);
	JCode pushInformationData(const NetworkData::JHead& head,const QByteArray& data,int msecs=30000);

	virtual NetworkData::JHead getHead(JID id)const=0;
	void sendInformationData(JID id,const QByteArray& data);
	bool waitForSendResult(JID id,int msecs=30000);
	JCode getSendResult(JID id);
	JCode pushInformationData(JID id,const QByteArray& data,int msecs=30000);
private:
	JClientInformationProcessor* m_processor;
	QMap<NetworkData::JHead,JCode> m_sendResults;
private slots:
	void on_processor_receiveUploadResult(const NetworkData::JHead& head,JCode result);
};

#endif // JINFORMATIONSENDBASE_H
