#ifndef JREMEMBERPASSWORD_H
#define JREMEMBERPASSWORD_H

#include <QString>
#include <QSettings>

class JRememberPassword
{
public:
    JRememberPassword();
    const QString& getUserName()const;
    const QString& getPassWord()const;
	int getRole()const;
    void changeUserName(const QString&);
    void setPassWord(const QString&);
	void setRole(int role);
    void remember();
    void remove();
private:
    QString m_username;
    QString m_password;
	int m_role;
    void updatePassWord();
	void updateRole();
    void readDefaultUserName();
    void readPassWord();
	void readRole();
    void writeDefaultUserName();
    void writePassWord();
	void writeRole();
protected:
    QSettings m_setting;
    virtual const QString& getfileName()const;
    virtual QSettings::Format getFormat()const;
};

#endif // JREMEMBERPASSWORD_H
