#ifndef JUSERSTATEMANAGER_H
#define JUSERSTATEMANAGER_H

#include <Global/Global>

class JUserStateManager
{
public:
    JUserStateManager();
	enum EState{
		ES_OffLine,
		ES_OnLine,
	};
	void setUserState(JID userId,EState state);
	EState getUserState(JID userId)const;
};

#endif // JUSERSTATEMANAGER_H
