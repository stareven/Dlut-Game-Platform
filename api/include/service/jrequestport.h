#ifndef JREQUESTPORT_H
#define JREQUESTPORT_H

#include <QObject>
#include <QMap>

#include "global/eportsrv.h"
#include "global/shost.h"

#include "clientapi_global.h"

class JRequestPortSocket;

class CLIENTAPISHARED_EXPORT JRequestPort : public QObject
{
    Q_OBJECT
public:
    explicit JRequestPort(QObject *parent = 0);
    void setServerPort(EServerType,const SHost&);
    SHost rqsServerPort(EServerType);
	SHost getServerPort(EServerType)const;
	const QString& getError()const;
protected:
	bool passLoginHash(JRequestPortSocket&);
protected slots:
    void on_socket_rcvPassLoginHash(bool);
    void on_socket_rcvServerPort(quint16);
	void on_socket_SocketError(const QString&);
private:
    //pass login hash
    //0 failed
    //1 success
    //-1 init
    //-2 rqs ing
    int m_plh;
    quint16 m_port;
	QString m_error;
private:
    static QMap<EServerType,SHost> s_ports;
};

#endif // JREQUESTPORT_H
