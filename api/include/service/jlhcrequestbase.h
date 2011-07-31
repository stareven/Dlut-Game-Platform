#ifndef JLHCREQUESTBASE_H
#define JLHCREQUESTBASE_H

#include "service/jrequestbase.h"

class JLhcSocketBase;

class JLhcRequestBase : public JRequestBase
{
	Q_OBJECT
public:
	explicit JLhcRequestBase(QObject *parent = 0);
	void sendLoginHashCode(JID,const QByteArray&);
	enum ELhcState{///< Login hash confirm的状态。
		EPS_Init,///< 初始状态
		EPS_Sending,///< 已经发送但仍未收到结果
		EPS_Success,///< 发送成功
		EPS_Failed,///< 发送失败
	};
	ELhcState getLhcState()const;
	bool waitForLhc(int msecs = 30000 )const;
protected:
	void setSocket(JLhcSocketBase*);
signals:
	void lhcResult(bool);
private slots:
	void on_socket_rcvLoginHashConfirm(bool);
private:
	JLhcSocketBase* m_socket;
	ELhcState m_state;
};

#endif // JLHCREQUESTBASE_H
