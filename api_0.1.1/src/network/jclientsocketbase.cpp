#include "jclientsocketbase.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QCoreApplication>

#include "../global/shost.h"

JClientSocketBase::JClientSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
}

JClientSocketBase* JClientSocketBase::getInstance(){
    static JClientSocketBase* instance=NULL;
    if(NULL==instance){
        instance = new JClientSocketBase(
                        new QTcpSocket(QCoreApplication::instance()),
                        QCoreApplication::instance());
    }
    return instance;
}

void JClientSocketBase::connectToServer(const SHost& host){
    if(m_socket->state()==QAbstractSocket::ConnectedState)
    {
        if(m_socket->peerAddress()==host.m_address&& m_socket->peerPort()==host.m_port)
        {
            return;
        }else{
            m_socket->disconnectFromHost();
        }
    }
    m_socket->connectToHost(host.m_address,host.m_port);
}
