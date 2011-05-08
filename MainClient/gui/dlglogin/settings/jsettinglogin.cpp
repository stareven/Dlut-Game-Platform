#include "jsettinglogin.h"

JSettingLogin::JSettingLogin()
{
    read();
}

const QString& JSettingLogin::getfileName()const
{
    static QString fn="login.ini";
    return fn;
}

bool JSettingLogin::getIsRemember()const
{
    return m_isRemember;
}

void JSettingLogin::setIsRemember(bool remember)
{
    if(m_isRemember!=remember) m_isRemember=remember;
}

bool JSettingLogin::getIsAutoLogin()const
{
    return m_isAutoLogin;
}

void JSettingLogin::setIsAutoLogin(bool autologin)
{
    if(m_isAutoLogin!=autologin) m_isAutoLogin=autologin;
}

void JSettingLogin::remember()
{
    write();
    if(getIsRemember()) JRememberPassword::remember();
    else JRememberPassword::remove();
}

void JSettingLogin::read()
{
    m_isRemember=m_setting.value("default/isRemember").toBool();
    m_isAutoLogin=m_setting.value("default/isAutoLogin").toBool();
}

void JSettingLogin::write()
{
    m_setting.setValue("default/isRemember",m_isRemember);
    m_setting.setValue("default/isAutoLogin",m_isAutoLogin);
}
