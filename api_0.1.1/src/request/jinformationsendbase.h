#ifndef JINFORMATIONSENDBASE_H
#define JINFORMATIONSENDBASE_H

#include "jinformation.h"
#include <QMap>

#include "jrequestbase.h"

class JClientUploadInformationProcessor;

class JInformationSendBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JInformationSendBase(QObject *parent = 0);
	void sendInformationData(const NetworkData::JHead& head,const QByteArray& data);
	bool waitForSendResult(const NetworkData::JHead& head,int msec=30000);
	JCode getSendResult(const NetworkData::JHead& head);
	JCode pushInformationData(const NetworkData::JHead& head,int msec=30000);

	virtual NetworkData::JHead getHead(JID id)const=0;
	void sendInformationData(JID id,const QByteArray& data);
	bool waitForSendResult(JID id,int msec=30000);
	JCode getSendResult(JID id);
	JCode pushInformationData(JID,int msec=30000);
private:
	JClientUploadInformationProcessor* m_processor;
	QMap<NetworkData::JHead,JCode> m_sendResults;
private slots:
	void on_processor_receiveSendInformationResult(const NetworkData::JHead& head,JCode result);
};

#endif // JINFORMATIONSENDBASE_H
