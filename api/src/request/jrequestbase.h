#ifndef JREQUESTBASE_H
#define JREQUESTBASE_H

#include <QObject>

#include "../global/jglobal.h"

class QHostAddress;

class JRequestBase : public QObject
{
	Q_OBJECT
public:
	JRequestBase(QObject *parent = 0);
    void connectToHost(const QHostAddress& address,quint16 port);
	bool waitForConnected(int msecs=30000)const;
    const QString& getConnectError()const;
signals:
	void error();
private:
    QString m_error;
private slots:
	void on_socket_SocketError(const QString&);
};

#endif // JREQUESTBASE_H
