#ifndef JREQUESTLOGIN_H
#define JREQUESTLOGIN_H

#include <QObject>

#include "global/jglobal.h"

class QHostAddress;
class JRequestLoginSocket;

class JRequestLogin : public QObject
{
    Q_OBJECT
public:
    explicit JRequestLogin(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,
                       quint16 port);
    void login(const QString& loginname,
               const QString& passwd,
               const JID& role);
    enum EState{
        ES_Close,
        ES_Connecting,
        ES_Connected,
        ES_Logining,
        ES_Logined,
        ES_Error
    };
    EState state()const;
	bool waitForConnected( int msecs = 30000 )const;
    bool waitForLogined(int msecs=30000);
    const QString& error()const;
signals:
    void connected();
    void disconnected();
    void error(const QString&);
protected slots:
    void on_socket_loginCode(JCode);
	void on_socket_SocketCode(JCode);
private:
    EState m_state;
	JRequestLoginSocket *m_socket;
    int m_error;
};

#endif // JREQUESTLOGIN_H
