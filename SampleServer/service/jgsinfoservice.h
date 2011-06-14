#ifndef JGSINFOSERVICE_H
#define JGSINFOSERVICE_H

#include <QObject>

#include "jglobal.h"

class QHostAddress;
class JGsInfoSocket;
class SGameInfo;
namespace SubServer
{
	class SSubServer;
	class SGameInfo2;
}

class JGsInfoService : public QObject
{
    Q_OBJECT
public:
    explicit JGsInfoService(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,
                       quint16 port);
    void sendCrypro(JID,const QByteArray&);
//    void sendGsInfo(const SGameInfo&);
	void sendServerInfo(const SubServer::SSubServer&);
	void sendGameInfo(const SubServer::SGameInfo2&);
    enum EState{
        ES_Close,//0
        ES_Connecting,//1
        ES_Connected,//2
        ES_SendingPlh,//3
		ES_PlhSuccess,//4
		ES_Sending,//5
		ES_SendSuccess,//6
		ES_Error//7
    };
    EState state()const;
    bool waitForConnected(int msecs=30000);
    bool waitForPassLoginHash(int msecs=30000);
    bool waitForSend(int msecs=30000);
    const QString& error()const;
signals:
    void connected();
    void disconnected();
    void error(const QString&);
    void passLoginHash(bool);
	void rcvSendCode(JID protocol,JCode code);
protected slots:
    void on_socket_rcvPassLoginHash(bool);
	void on_socket_rcvSendCode(JID protocol,JCode code);
    void on_socket_SocketCode(JCode);
private:
    EState m_state;
    JGsInfoSocket* m_socket;
    int m_error;
    bool m_plh;
};

#endif // JGSINFOSERVICE_H
