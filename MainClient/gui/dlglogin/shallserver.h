#ifndef SHALLSERVER_H
#define SHALLSERVER_H

#include <QString>
#include <QHostAddress>

#include "global/shost.h"

class SHallServer
{
public:
    SHallServer();
	SHallServer(const QHostAddress&,quint16);
    const QString& toString()const;
    const QHostAddress& getAddress()const;
    quint16 getPort()const;
	operator SHost()const;
//    const QString& getName()const;
//    void setName(const QString&);
    bool isEmpty()const;
private:
//    QString m_name;
    QHostAddress m_address;
    quint16 m_port;
    QString m_string;
    void updateString();
};

#endif // SHALLSERVER_H
