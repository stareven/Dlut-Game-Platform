#include "jgsinfoservice.h"

#include <QElapsedTimer>
#include <QCoreApplication>

#include "network/jgsinfosocket.h"

JGsInfoService::JGsInfoService(QObject *parent) :
    QObject(parent)
{
    m_state=ES_Close;
    m_socket=new JGsInfoSocket(this);
    m_error=0;
    m_plh=false;
    connect(m_socket,SIGNAL(rcvPassLoginHash(bool)),SLOT(on_socket_rcvPassLoginHash(bool)));
    connect(m_socket,SIGNAL(rcvGsInfo(JID)),SLOT(on_socket_rcvGsInfo(JID)));
    connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
}

void JGsInfoService::connectToHost(const QHostAddress& address,
                   quint16 port)
{
    m_state=ES_Connecting;
    m_socket->connectToHost(address,port);
}

void JGsInfoService::sendCrypro(JID id,const QByteArray& data)
{
    m_state=ES_SendingPlh;
    m_socket->sendCrypro(id,data);
}

void JGsInfoService::sendGsInfo(const SGameInfo& gi)
{
    m_state=ES_SendingGi;
    m_socket->sendGsInfo(gi);
}

JGsInfoService::EState JGsInfoService::state()const
{
    return m_state;
}

bool JGsInfoService::waitForConnected(int msecs)
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

bool JGsInfoService::waitForPassLoginHash(int msecs)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
        if(state()!=ES_SendingPlh)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
    return state()==ES_PlhSuccess;
}

bool JGsInfoService::waitForSend(int msecs)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
        if(state()!=ES_SendingGi)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
    return state()==ES_SendGiSuccess;
}

const QString& JGsInfoService::error()const
{
    static const QString errors[]={
        tr("no error"),//0
        tr("socket can not write"),//1
        tr("socket disconnected"),//2
        tr("pass login hash failed"),//3
        tr("send game info failed"),//4
    };
    return errors[m_error];
}

void JGsInfoService::on_socket_rcvPassLoginHash(bool plh)
{
//    qDebug()<<"JGsInfoService::on_socket_rcvPassLoginHash"<<plh;
    if(plh)
    {
        m_state=ES_PlhSuccess;
        m_error=0;
    }else{
        m_state=ES_Error;
        m_error=3;
    }
}

void JGsInfoService::on_socket_rcvGsInfo(JID id)
{
//    qDebug()<<"JGsInfoService::on_socket_rcvGsInfo";
    if(id<0)
    {
        m_state=ES_Error;
        m_error=4;
    }else{
        m_state=ES_SendGiSuccess;
    }
}

void JGsInfoService::on_socket_SocketCode(JCode code)
{
    switch(code)
    {
    case EN_CONNECTED:
        m_state=ES_Connected;
        m_error=0;
        emit connected();
        break;
    case EN_DISCONNECTED:
        m_state=ES_Error;
        m_error=2;
        emit disconnected();
        break;
    }
}
