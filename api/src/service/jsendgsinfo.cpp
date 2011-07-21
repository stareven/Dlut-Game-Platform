#include "service/jsendgsinfo.h"

#include <QCoreApplication>

#include "network/jsendgsinfosocket.h"
#include "global/jelapsedtimer.h"

JSendGsInfo::JSendGsInfo(QObject *parent) :
    QObject(parent)
{
    m_state=ES_Close;
    m_socket=new JSendGsInfoSocket(this);
    m_error=0;
    m_plh=false;
    connect(m_socket,SIGNAL(rcvPassLoginHash(bool)),SLOT(on_socket_rcvPassLoginHash(bool)));
	connect(m_socket,SIGNAL(rcvSendCode(JID,JCode)),SLOT(on_socket_rcvSendCode(JID,JCode)));
    connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
}

void JSendGsInfo::connectToHost(const QHostAddress& address,
                   quint16 port)
{
    m_state=ES_Connecting;
    m_socket->connectToHost(address,port);
}

void JSendGsInfo::sendCrypro(JID id,const QByteArray& data)
{
    m_state=ES_SendingPlh;
    m_socket->sendCrypro(id,data);
}

void JSendGsInfo::sendServerInfo(const SubServer::SSubServer& ss)
{
	m_state=ES_Sending;
	m_socket->sendServerInfo (ss);
}

void JSendGsInfo::sendGameInfo(const SubServer::SGameInfo2& gi)
{
	m_state=ES_Sending;
	m_socket->sendGameInfo (gi);
}

void JSendGsInfo::sendRelation(JID serverId,
								  JID gameId,
								  const JVersion& gameVersion)
{
	m_state=ES_Sending;
	m_socket->sendRelation(serverId,gameId,gameVersion);
}

JSendGsInfo::EState JSendGsInfo::state()const
{
    return m_state;
}

bool JSendGsInfo::waitForConnected(int msecs)
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

bool JSendGsInfo::waitForPassLoginHash(int msecs)
{
    JElapsedTimer timer;
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

bool JSendGsInfo::waitForSend(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
		if(state()!=ES_Sending)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
	return state()==ES_SendSuccess;
}

const QString& JSendGsInfo::error()const
{
    static const QString errors[]={
        tr("no error"),//0
        tr("socket can not write"),//1
        tr("socket disconnected"),//2
        tr("pass login hash failed"),//3
		tr("send failed"),//4
    };
    return errors[m_error];
}

void JSendGsInfo::on_socket_rcvPassLoginHash(bool plh)
{
    if(plh)
    {
        m_state=ES_PlhSuccess;
        m_error=0;
    }else{
        m_state=ES_Error;
        m_error=3;
    }
}

void JSendGsInfo::on_socket_rcvSendCode(JID protocol,JCode code)
{
	qDebug()<<"JSendGsInfo::on_socket_rcvSendCode . protocol="
			<<protocol
			<<"code="
			<<code;
	if(0==code)
	{
		m_state=ES_SendSuccess;
		m_error=0;
	}else{
		m_state=ES_Error;
		m_error=4;
	}
}

void JSendGsInfo::on_socket_SocketCode(JCode code)
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
