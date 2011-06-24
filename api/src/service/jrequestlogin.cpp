#include "service/jrequestlogin.h"

#include <QCoreApplication>

#include "network/jrequestloginsocket.h"
#include "global/elogin.h"
#include "service/jcryprorecorder.h"
#include "global/jelapsedtimer.h"

JRequestLogin::JRequestLogin(QObject *parent) :
    QObject(parent)
{
    m_socket=new JRequestLoginSocket(this);
    m_state=ES_Close;
    m_error=0;
    connect(m_socket,SIGNAL(loginCode(JCode)),SLOT(on_socket_loginCode(JCode)));
	connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
}

void JRequestLogin::connectToHost(const QHostAddress& address,quint16 port)
{
    m_state=ES_Connecting;
    m_socket->connectToHost(address,port);
}

void JRequestLogin::login(const QString& loginname,
           const QString& passwd,
           const JID& role)
{
    m_state=ES_Logining;
    m_socket->login(loginname,passwd,role);
}

JRequestLogin::EState JRequestLogin::state()const
{
    return m_state;
}

bool JRequestLogin::waitForConnected( int msecs)const
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
        if(state()!=ES_Connecting)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
    return state()==ES_Connected;
}

bool JRequestLogin::waitForLogined(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
        if(state()!=ES_Logining)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
    return state()==ES_Logined;
}

const QString& JRequestLogin::error()const
{
    static QString noerror="no error";
	if(EL_SUCCESS==m_error) return noerror;
    return loginMsg[m_error];
}

void JRequestLogin::on_socket_loginCode(JCode code)
{
    switch(code)
	{
    case EL_SUCCESS:
        m_state=ES_Logined;
        {
            JCryproRecorder cr;
            cr.set(m_socket->getCrypro(),m_socket->getUserId());
        }
        break;
    default:
        m_state=ES_Error;
        m_error=code;
        break;
    }
}

void JRequestLogin::on_socket_SocketCode(JCode code)
{
	switch((ENet)code)
	{
	case EN_CONNECTED:
		m_state=ES_Connected;
		m_error=EL_SUCCESS;
		break;
	case EN_DISCONNECTED:
		m_state=ES_Error;
		m_error=EL_SOCKET_DISCONNECTED;
		break;
	}
}
