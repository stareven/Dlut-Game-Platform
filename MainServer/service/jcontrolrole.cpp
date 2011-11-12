#include "jcontrolrole.h"

#include "../database/jabstractdatabasefactory.h"

#include <QDebug>

JControlRole::JControlRole()
{
	m_dbFactory=JAbstractDatabaseFactory::getInstance();
}

void JControlRole::execute(JID targetUserId,ERole targetRole,EControlRoleAction act)
{
	JAbstractLoginDB* loginDB = m_dbFactory->createLoginDB();
	JRoleCombination role = loginDB->getRoleCombination(targetUserId);
	qDebug()<<"formerRole"<<role;
	switch(act){
	case ECRA_Add:
		role |= (1<<targetRole);
		break;
	case ECRA_Remove:
		role &= ~(1<<targetRole);
		break;
	}
	qDebug()<<"afterRole"<<role;
	loginDB->setRoleCombination(targetUserId,role);
}
