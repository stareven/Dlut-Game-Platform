#ifndef JREQUESTBASE_H
#define JREQUESTBASE_H

#include <QObject>

#include "global/jglobal.h"
#include "clientapi_global.h"

class QHostAddress;
class JSocketBase;

class CLIENTAPISHARED_EXPORT JRequestBase : public QObject
{
	Q_OBJECT
public:
	JRequestBase(QObject *parent = 0);
	void connectToHost(const QHostAddress& address,quint16 port);
	/// 连接状态。
	enum EConnectState{
		ECS_Init, ///< 初始状态
		ECS_Connecting, ///< 开始向服务器发起连接
		ECS_Connected, ///< 已经成功连接到服务器
		ECS_Error, ///< 发生错误
	};
	EConnectState getConnectState()const;
	bool waitForConnected(int msecs=30000)const;
	const QString& getConnectError()const;
protected:
	void setSocket(JSocketBase* socket);
signals:
	void connectResult(bool);
	void error();
private:
	JSocketBase* m_socket;
	EConnectState m_state;
	const QString* m_error;
private slots:
	void on_socket_SocketCode(ENet netcode);
	void on_socket_SocketError(const QString&);
};

#endif // JREQUESTBASE_H
