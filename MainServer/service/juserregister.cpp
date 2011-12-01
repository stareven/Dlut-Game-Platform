#include "juserregister.h"

#include "database/jabstractdatabasefactory.h"
#include "database/jabstractlogindb.h"
#include <Global/Register>

JUserRegister::JUserRegister(JID runnerId)
{
	m_runnerId=runnerId;
	m_result=-1;
	m_userId = -1;
}

void JUserRegister::execute(const QString& loginname,const QString& password,ERole role)
{
	JAbstractLoginDB* logindb=JAbstractDatabaseFactory::getInstance()->createLoginDB();
	if(-1 == m_runnerId){
		if(role != ROLE_GAMEPLAYER){
			m_result = ER_PermissionDenied;
			return;
		}
	}else{
		JRoleCombination rc = logindb->getRoleCombination(m_runnerId);
		if( (rc>>1) < (1<<role) ){
			m_result = ER_PermissionDenied;
			return;
		}
	}
	if(logindb->checkLoginName(loginname)>=0){
		m_result = ER_LoginNameExists;
		return;
	}
	if(loginname.length()<4 || loginname.length() >15){
		m_result = ER_LoginNameLengthError;
		return;
	}
	if(password.length() <3 || password.length() >50){
		m_result = ER_PasswordLengthError;
		return;
	}
	m_result=logindb->addLoginUser(loginname,password);
	if(0==m_result){
		m_userId = logindb->checkLoginName(loginname);
		m_loginname = logindb->getLoginName(m_userId);
	}
}

JCode JUserRegister::getResult()const
{
	return m_result;
}

JID JUserRegister::getUserId()const
{
	return m_userId;
}

const QString& JUserRegister::getLoginname()const
{
	return m_loginname;
}
