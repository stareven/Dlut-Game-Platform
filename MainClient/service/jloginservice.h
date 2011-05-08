#ifndef JLOGINSERVICE_H
#define JLOGINSERVICE_H

#include <QObject>

#include "jglobal.h"

class QHostAddress;
class JLoginSocket;

class JLoginService : public QObject
{
Q_OBJECT
public:
    explicit JLoginService(QObject *parent = 0);
    void login(const QString& loginname,
	       const QString& passwd,
	       const JID& role,
	       const QHostAddress& address,
               quint16 port);
signals:
    void loginMsg(JCode);
private slots:
    void on_socket_loginCode(JCode);
private:
    QString m_loginname;
    QString m_passwd;
    JID m_role;
    JLoginSocket *m_socket;
};

#endif // JLOGINSERVICE_H
