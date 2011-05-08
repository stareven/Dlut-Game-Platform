#ifndef JPORTSERVICE_H
#define JPORTSERVICE_H

#include <QObject>
#include <QMap>

#include "eportsrv.h"

class JPortSocket;

class JPortService : public QObject
{
    Q_OBJECT
public:
    explicit JPortService(QObject *parent = 0);
    void setServerPort(EServerType,const SHost&);
    SHost rqsServerPort(EServerType);
    SHost getServerPort(EServerType)const;
protected:
    bool passLoginHash(JPortSocket&);
protected slots:
    void on_socket_rcvPassLoginHash(bool);
    void on_socket_rcvServerPort(quint16);
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
    quint16 m_port;
private:
    static QMap<EServerType,SHost> s_ports;
};

#endif // JPORTSERVICE_H
