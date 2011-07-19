#include "jrememberpassword.h"

JRememberPassword::JRememberPassword()
    :m_setting(getfileName(),getFormat())//*"login.ini",*/QSettings::IniFormat)
{
    readDefaultUserName();
}

const QString& JRememberPassword::getUserName()const
{
    return m_username;
}

const QString& JRememberPassword::getPassWord()const
{
    return m_password;
}

int JRememberPassword::getRole()const
{
	return m_role;
}

void JRememberPassword::changeUserName(const QString& username)
{
    if(m_username!=username)
    {
        m_username=username;
        updatePassWord();
		updateRole();
    }
}

void JRememberPassword::setPassWord(const QString& pswd)
{
    m_password=pswd;
}

void JRememberPassword::setRole(int role)
{
	m_role=role;
}

void JRememberPassword::remember()
{
    writeDefaultUserName();
    writePassWord();
	writeRole();
}

void JRememberPassword::remove()
{
    m_setting.remove(m_username);
}

void JRememberPassword::updatePassWord()
{
    readPassWord();
}

void JRememberPassword::updateRole()
{
	readRole();
}

void JRememberPassword::readDefaultUserName()
{
    m_username=m_setting.value("default/username").toString();
    updatePassWord();
	updateRole();
}

void JRememberPassword::readPassWord()
{
    m_password=m_setting.value(QString("%1/password").arg(m_username)).toString();
}

void JRememberPassword::readRole()
{
	m_role=m_setting.value(QString("%1/role").arg(m_username)).toInt();
}

void JRememberPassword::writeDefaultUserName()
{
    m_setting.setValue("default/username",m_username);
}

void JRememberPassword::writePassWord()
{
    m_setting.setValue(QString("%1/password").arg(m_username),m_password);
}

void JRememberPassword::writeRole()
{
	m_setting.setValue(QString("%1/role").arg(m_username),m_role);
}

const QString& JRememberPassword::getfileName()const
{
    static QString fn="login.ini";//,QSettings::IniFormat
    return fn;
}
QSettings::Format JRememberPassword::getFormat()const
{
    return QSettings::IniFormat;
}
