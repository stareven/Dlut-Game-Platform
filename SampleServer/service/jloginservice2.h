#ifndef JLOGINSERVICE2_H
#define JLOGINSERVICE2_H

#include <QObject>

#include "jglobal.h"

class QHostAddress;
class JLoginSocket;

class JLoginService2 : public QObject
{
    Q_OBJECT
public:
    explicit JLoginService2(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,quint16 port);
    void login(const QString& loginname,
               const QString& passwd,
               const JID& role);
    enum EState{ES_Close,ES_Connecting,ES_Connected,ES_Logining,ES_Logined,ES_Error};
    EState state()const;
    bool waitForConnected( int msecs = 30000 );
    bool waitForLogined(int msecs=30000);
    const QString& error()const;
signals:
    void connected();
    void disconnected();
    void error(const QString&);
protected slots:
    void on_socket_loginCode(JCode);
private:
    EState m_state;
    JLoginSocket *m_socket;
    int m_error;
};

#endif // JLOGINSERVICE2_H
