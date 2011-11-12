#ifndef JCONTROLROLE_H
#define JCONTROLROLE_H

#include <Global/Global>
#include <Global/Login>

class JAbstractDatabaseFactory;

class JControlRole
{
public:
    JControlRole();
	void execute(JID targetUserId,ERole targetRole,EControlRoleAction act);
private:
	JAbstractDatabaseFactory* m_dbFactory;
};

#endif // JCONTROLROLE_H
