#ifndef JINFORMATIONREQUESTBASE_H
#define JINFORMATIONREQUESTBASE_H

#include "jrequestbase.h"

namespace NetworkData{
	class JHead;
}
class JInformationRequestBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JInformationRequestBase(QObject *parent = 0);
	void setDefaultOldLimit(JTime_t);
	/// return true if need request
	bool rqsModifyTime(const NetworkData::JHead& head);
	bool rqsModifyTime(const NetworkData::JHead &head,JTime_t oldLimit);
	bool waitForModifyTime(const NetworkData::JHead& head,int msec=30000);
	bool rqsInfomationData(const NetworkData::JHead& head);
	bool rqsInfomationData(const NetworkData::JHead& head,JTime_t oldLimit);
	bool waitForInfomationData(const NetworkData::JHead& head,int msec=30000);
	JTime_t getModifyTime(const NetworkData::JHead& head);
	QByteArray getInfomationData(const NetworkData::JHead& head);
signals:
	void rcvModifyTime(const NetworkData::JHead& head,
					   JTime_t modifyTime);
	void rcvInfomationData(const NetworkData::JHead& head,
						   const QByteArray& data);
private:
	JTime_t m_defaultOldLimit;
};

#endif // JINFORMATIONREQUESTBASE_H
