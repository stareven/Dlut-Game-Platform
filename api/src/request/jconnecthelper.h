#ifndef JCONNECTHELPER_H
#define JCONNECTHELPER_H

#include <QObject>

#include "../global/jglobal.h"

class SHost;
class JClientSocketBase;

class JConnectHelper : public QObject
{
    Q_OBJECT
public:
	explicit JConnectHelper(JClientSocketBase* socket,QObject *parent = 0);
	void connectToHost(const SHost& host);
	bool waitForConnected(int msecs=30000)const;
	const QString& getConnectError()const;
signals:
	void error();
private:
	QString m_error;
	JClientSocketBase* m_socket;
private slots:
	void on_socket_SocketError(JCode errorCode);
};

#endif // JCONNECTHELPER_H
