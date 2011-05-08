#include "jloginservice.h"

#include "network/jloginsocket.h"
#include "jcryprorecorder.h"

#include "elogin.h"

JLoginService::JLoginService(QObject *parent) :
    QObject(parent)
{
    m_socket=new JLoginSocket(this);
    connect(m_socket,SIGNAL(loginCode(JCode)),this,SLOT(on_socket_loginCode(JCode)));
}

void JLoginService::login(const QString& loginname,
			  const QString& passwd,
			  const JID& role,
			  const QHostAddress& address,
			  quint16 port)
{
    m_loginname=loginname;
    m_passwd=passwd;
    m_role=role;
    emit loginMsg(EL_BEGIN_TO_LOGIN);
    m_socket->connectToHost(address,port);
}

void JLoginService::on_socket_loginCode(JCode code)
{
//    if(EL_CONNECTED==code)
//    {
//	m_socket->login(m_loginname,m_passwd,m_role);
//    }
    switch(code)
    {
    case EL_CONNECTED:
        m_socket->login(m_loginname,m_passwd,m_role);
        break;
    case EL_SUCCESS:
        {
            JCryproRecorder cr;
            cr.set(m_socket->getCrypro(),m_socket->getUserId());
        }
        break;
    }
    emit loginMsg(code);
}
