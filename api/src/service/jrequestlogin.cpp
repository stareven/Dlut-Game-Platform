#include "service/jrequestlogin.h"

#include <QCoreApplication>

#include "network/jrequestloginsocket.h"
#include "global/elogin.h"
#include "service/jcryprorecorder.h"
#include "global/jelapsedtimer.h"

JRequestLogin::JRequestLogin(QObject *parent) :
	JRequestBase(parent)
{
    m_socket=new JRequestLoginSocket(this);
	setSocket(m_socket);
	m_state=ELS_Init;
	m_loginError=EL_SUCCESS;
    connect(m_socket,SIGNAL(loginCode(JCode)),SLOT(on_socket_loginCode(JCode)));
}

void JRequestLogin::login(const QString& loginname,
           const QString& passwd,
           const JID& role)
{
	m_state=ELS_Sending;
    m_socket->login(loginname,passwd,role);
}

JRequestLogin::ELoginState JRequestLogin::getLoginState()const
{
    return m_state;
}

bool JRequestLogin::waitForLogined(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
		if(getLoginState()!=ELS_Sending)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
	return getLoginState()==ELS_Success;
}

const QString& JRequestLogin::getLoginError()const
{
    static QString noerror="no error";
	if(EL_SUCCESS==m_loginError) return noerror;
	return loginMsg[m_loginError];
}

void JRequestLogin::on_socket_loginCode(JCode code)
{
    switch(code)
	{
    case EL_SUCCESS:
		m_state=ELS_Success;
        {
            JCryproRecorder cr;
            cr.set(m_socket->getCrypro(),m_socket->getUserId());
        }
		emit loginResult(true);
        break;
    default:
		m_state=ELS_Failed;
		m_loginError=(ELogin)code;
		emit loginResult(false);
        break;
    }
}

