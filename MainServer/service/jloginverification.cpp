#include "jloginverification.h"

#include <QString>
#include <QCryptographicHash>

#include "database/jabstractdatabasefactory.h"
#include "database/jabstractlogindb.h"

JLoginVerification::JLoginVerification()
{
    m_userid=-1;
}

/// return 0 if succeed
/// return 1 if no such user
/// return 2 if password wrong
/// return 3 if no such role
ELogin JLoginVerification::verification(const QString& loginname,const QString& passwd,const ERole& role)
{
	JAbstractLoginDB* logindb=JAbstractDatabaseFactory::getInstance()->createLoginDB();
	JID id=logindb->checkLoginName(loginname);
    if(id<0) return EL_NO_SUCH_USER;
	if(!logindb->checkPasswd(id,passwd)) return EL_PASSWD_WRONG;
	if(!logindb->checkRole(id,role)) return EL_NO_SUCH_ROLE;
    m_userid=id;
    QByteArray data;
    data.append(loginname);
    data.append(passwd);
    return EL_SUCCESS;
}

/// return userid if succeed , -1 if failed
JID JLoginVerification::JLoginVerification::getUserId()const
{
    return m_userid;
}
