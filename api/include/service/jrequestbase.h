#ifndef JREQUESTBASE_H
#define JREQUESTBASE_H

#include <QObject>

class QHostAddress;
class JSocketBase;

class JRequestBase : public QObject
{
	Q_OBJECT
public:
	JRequestBase(QObject *parent = 0);
	void connectToHost(const QHostAddress& address,quint16 port);
	enum EConnectState{
		ECS_Init,
		ECS_Connecting,
		ECS_Connected,
		ECS_Error,
	};
	EConnectState getConnectState()const;
	bool waitForConnected(int msecs=30000)const;
	const QString& error()const;
private:
	JSocketBase* m_socket;
	EConnectState m_state;
	const QString* m_error;
};

#endif // JREQUESTBASE_H
