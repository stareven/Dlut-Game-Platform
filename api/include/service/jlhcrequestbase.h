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
	enum ELhcState{
		EPS_Init,
		EPS_Sending,
		EPS_Success,
		EPS_Failed,
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
