#ifndef JPLHREQUESTBASE_H
#define JPLHREQUESTBASE_H

#include "service/jrequestbase.h"

class JPlhSocketBase;

class JPlhRequestBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JPlhRequestBase(QObject *parent = 0);
	void sendCrypro(JID,const QByteArray&);
	enum EPlhState{
		EPS_Init,
		EPS_Sending,
		EPS_Success,
		EPS_Failed,
	};
	EPlhState getPlhState()const;
	bool waitForPlh(int msecs = 30000 )const;
	void setSocket(JPlhSocketBase*);
private slots:
	void on_socket_rcvPassLoginHash(bool);
private:
	JPlhSocketBase* m_socket;
	EPlhState m_state;
};

#endif // JPLHREQUESTBASE_H
