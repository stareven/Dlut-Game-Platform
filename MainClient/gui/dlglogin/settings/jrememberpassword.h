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
    void changeUserName(const QString&);
    void setPassWord(const QString&);
    void remember();
    void remove();
private:
    QString m_username;
    QString m_password;
    void updatePassWord();
    void readDefaultUserName();
    void readPassWord();
    void writeDefaultUserName();
    void writePassWord();
protected:
    QSettings m_setting;
    virtual const QString& getfileName()const;
    virtual QSettings::Format getFormat()const;
};

#endif // JREMEMBERPASSWORD_H
