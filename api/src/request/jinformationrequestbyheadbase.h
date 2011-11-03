#ifndef JINFORMATIONREQUESTBYHEADBASE_H
#define JINFORMATIONREQUESTBYHEADBASE_H

#include "jrequestbase.h"
#include "../network/jinformation.h"

#include <QSet>

class JClientInformationProcessor;

class JInformationRequestByHeadBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JInformationRequestByHeadBase(QObject *parent = 0);
	void rqsRemoteMtime(const NetworkData::JHead& head);
	bool waitForRemoteMtime(const NetworkData::JHead& head,int msecs=30000);
	void rqsInformationData(const NetworkData::JHead& head);
	bool waitForInformationData(const NetworkData::JHead& head,int msecs=30000);
	JTime_t getRemoteMtime(const NetworkData::JHead& head);
	JTime_t getLocalMtime(const NetworkData::JHead& head);
	QByteArray getInformationData(const NetworkData::JHead& head);
	/// a helper function
	QByteArray pullInformationData(const NetworkData::JHead& head,int msecs=30000);
signals:
	void rcvRemoteMtime(const NetworkData::JHead& head,
					   JTime_t remoteMtime);
	void rcvInformationData(const NetworkData::JHead& head,
						   JTime_t localMtime,
						   const QByteArray& data);
private:
	JClientInformationProcessor* m_processor;
	QSet<NetworkData::JHead> m_receivedRemoteMtime;
	QSet<NetworkData::JHead> m_receivedInformationData;
private slots:
	void on_processor_receiveRemoteMtime(const NetworkData::JHead& head,JTime_t remoteMtime);
	void on_processor_receiveData(const NetworkData::JHead& head,JTime_t localMtime,const QByteArray& data);
};

#endif // JINFORMATIONREQUESTBYHEADBASE_H
