#ifndef JINFORMATIONREQUESTBASE_H
#define JINFORMATIONREQUESTBASE_H

#include "jinformationrequestbyheadbase.h"

class JInformationRequestBase : public JInformationRequestByHeadBase
{
    Q_OBJECT
public:
	explicit JInformationRequestBase(QObject *parent = 0);

	virtual NetworkData::JHead getHeadById(JID id)const=0;
	void rqsRemoteMtimeById(JID id);
	bool waitForRemoteMtimeById(JID id,int msecs=30000);
	void rqsInformationDataById(JID id);
	bool waitForInformationDataById(JID id,int msecs=30000);
	JTime_t getRemoteMtimeById(JID id);
	JTime_t getLocalMtimeById(JID id);
	QByteArray getInformationDataById(JID id);
	/// a helper function
	QByteArray pullInformationDataById(JID id,int msecs=30000);
signals:
	void rcvRemoteMtime(JID id,
					   JTime_t remoteMtime);
	void rcvInformationData(JID id,
						   JTime_t localMtime,
						   const QByteArray& data);

};

#endif // JINFORMATIONREQUESTBASE_H
