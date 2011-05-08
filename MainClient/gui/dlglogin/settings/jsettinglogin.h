#ifndef JSETTINGLOGIN_H
#define JSETTINGLOGIN_H

#include "jrememberpassword.h"

class JSettingLogin : public JRememberPassword
{
public:
    JSettingLogin();
    bool getIsRemember()const;
    void setIsRemember(bool remember);
    bool getIsAutoLogin()const;
    void setIsAutoLogin(bool autologin);

    void remember();
private:
    void read();
    void write();

    bool m_isRemember;
    bool m_isAutoLogin;
protected:
    virtual const QString& getfileName()const;
};

#endif // JSETTINGLOGIN_H
