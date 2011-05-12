#include "jloginservice2.h"

#include <QElapsedTimer>
#include <QCoreApplication>

#include "network/jloginsocket.h"
#include "elogin.h"
#include "service/jcryprorecorder.h"

JLoginService2::JLoginService2(QObject *parent) :
    QObject(parent)
{
    m_socket=new JLoginSocket(this);
    m_state=ES_Close;
    m_error=0;
    connect(m_socket,SIGNAL(loginCode(JCode)),SLOT(on_socket_loginCode(JCode)));
}

void JLoginService2::connectToHost(const QHostAddress& address,quint16 port)
{
    m_state=ES_Connecting;
    m_socket->connectToHost(address,port);
}

void JLoginService2::login(const QString& loginname,
           const QString& passwd,
           const JID& role)
{
    m_state=ES_Logining;
    m_socket->login(loginname,passwd,role);
}

JLoginService2::EState JLoginService2::state()const
{
    return m_state;
}

bool JLoginService2::waitForConnected( int msecs)
{
    QElapsedTimer timer;
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

bool JLoginService2::waitForLogined(int msecs)
{
    QElapsedTimer timer;
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

//const static QString errors[]={
//    "no error",
//};

const QString& JLoginService2::error()const
{
    static QString noerror="no error";
    if(EL_SUCCESS==m_error||EL_CONNECTED==m_error) return noerror;
    return loginMsg[m_error];
}

void JLoginService2::on_socket_loginCode(JCode code)
{
    switch(code)
    {
    case EL_CONNECTED:
        m_state=ES_Connected;
        break;
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
