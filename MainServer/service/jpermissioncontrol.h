#ifndef JPERMISSIONCONTROL_H
#define JPERMISSIONCONTROL_H

#include <Global/Global>

namespace NetworkData{
	class JHead;
}

class JPermissionControl
{
public:
	JPermissionControl(JID userId);
	bool checkInformation(JID protocol,const NetworkData::JHead& head);
	bool checkCommand(JID type,JID param);
private:
	JID m_userId;
};

#endif // JPERMISSIONCONTROL_H
