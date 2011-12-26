#ifndef SHALLSERVER_H
#define SHALLSERVER_H

#include <QString>
#include <QHostAddress>

#include <DataStruct/SHost>

class SHallServer
{
public:
    SHallServer();
	SHallServer(const QHostAddress&,quint16);
    const QString& toString()const;
    const QHostAddress& getAddress()const;
    quint16 getPort()const;
	operator SHost()const;
    bool isEmpty()const;
private:
    QHostAddress m_address;
    quint16 m_port;
    QString m_string;
    void updateString();
};

#endif // SHALLSERVER_H
