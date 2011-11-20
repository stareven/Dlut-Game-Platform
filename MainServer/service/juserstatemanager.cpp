#include "juserstatemanager.h"

#include <QMap>

static QMap<JID,JUserStateManager::EState> g_states;

JUserStateManager::JUserStateManager()
{
}

void JUserStateManager::setUserState(JID userId,EState state)
{
	g_states[userId]=state;
}

JUserStateManager::EState JUserStateManager::getUserState(JID userId)const
{
	return g_states.value(userId,JUserStateManager::ES_OffLine);
}
