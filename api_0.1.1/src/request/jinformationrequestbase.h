#ifndef JINFORMATIONREQUESTBASE_H
#define JINFORMATIONREQUESTBASE_H

#include "../network/jinformation.h"
#include <QSet>

#include "jrequestbase.h"


class JClientDownloadInformationProcessor;

class JInformationRequestBase : public JRequestBase
{
    Q_OBJECT
public:
	explicit JInformationRequestBase(QObject *parent = 0);
	void rqsRemoteMtime(const NetworkData::JHead& head);
	bool waitForRemoteMtime(const NetworkData::JHead& head,int msecs=30000);
	void rqsInformationData(const NetworkData::JHead& head);
	bool waitForInformationData(const NetworkData::JHead& head,int msecs=30000);
	JTime_t getRemoteMtime(const NetworkData::JHead& head);
	JTime_t getLocalMtime(const NetworkData::JHead& head);
	QByteArray getInformationData(const NetworkData::JHead& head);
	/// a helper function
	QByteArray pullInformationData(const NetworkData::JHead& head,int msecs=30000);

	virtual NetworkData::JHead getHead(JID id)const=0;
	void rqsRemoteMtime(JID id);
	bool waitForRemoteMtime(JID id,int msecs=30000);
	void rqsInformationData(JID id);
	bool waitForInformationData(JID id,int msecs=30000);
	JTime_t getRemoteMtime(JID id);
	JTime_t getLocalMtime(JID id);
	QByteArray getInformationData(JID id);
	/// a helper function
	QByteArray pullInformationData(JID id,int msecs=30000);
signals:
	void rcvRemoteMtime(const NetworkData::JHead& head,
					   JTime_t remoteMtime);
	void rcvInformationData(const NetworkData::JHead& head,
						   JTime_t localMtime,
						   const QByteArray& data);

	void rcvRemoteMtime(JID id,
					   JTime_t remoteMtime);
	void rcvInformationData(JID id,
						   JTime_t localMtime,
						   const QByteArray& data);
private:
	JClientDownloadInformationProcessor* m_processor;
	QSet<NetworkData::JHead> m_receivedRemoteMtime;
	QSet<NetworkData::JHead> m_receivedInformationData;
private slots:
	void on_processor_receiveRemoteMtime(const NetworkData::JHead& head,JTime_t remoteMtime);
	void on_processor_receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray& data);
};

#endif // JINFORMATIONREQUESTBASE_H
