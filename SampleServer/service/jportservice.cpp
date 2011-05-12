#include "jportservice.h"

#include <QElapsedTimer>
#include <QCoreApplication>

#include "network/jportsocket.h"

#include "jcryprorecorder.h"

QMap<EServerType,SHost> JPortService::s_ports;

JPortService::JPortService(QObject *parent) :
    QObject(parent)
{
}

void JPortService::setServerPort(EServerType type,const SHost& host)
{
    s_ports.insert(type,host);
}

SHost JPortService::rqsServerPort(EServerType type)
{
    if(s_ports.contains(type))
    {
        return s_ports.value(type);
    }
    if(type==EST_FREEPORT)
    {
        qDebug()<<"free port not set!";
        return SHost(QHostAddress("127.0.0.1"),37373);
    }
    JPortSocket socket;
    SHost host;
    if(isInFree(type))
    {
        host=rqsServerPort(EST_FREEPORT);
    }else{
        host=rqsServerPort(EST_SECRETPORT);
    }
    socket.connectToHost(host.m_address,host.m_port);
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<1000)
    {
        if(socket.isConnected()) break;
        QCoreApplication::processEvents();
    }
    if(!socket.isConnected())
    {
        qDebug()<<"connect time out.";
        return SHost();
    }
    if(!isInFree(type))
    {
        connect(&socket,SIGNAL(rcvPassLoginHash(bool)),SLOT(on_socket_rcvPassLoginHash(bool)));
        if(!passLoginHash(socket))
        {
            qDebug()<<"pass login hash time out.";
            return SHost();
        }
    }
    m_port=0;
    connect(&socket,SIGNAL(rcvServerPort(quint16)),SLOT(on_socket_rcvServerPort(quint16)));
    socket.rqsServerPort(type);
    timer.restart();
    while(timer.elapsed()<1000)
    {
        if(m_port) break;
        QCoreApplication::processEvents();
    }
    if(!m_port)
    {
        qDebug()<<"connect time out.";
        return SHost();
    }
    s_ports.insert(type,SHost(QHostAddress("127.0.0.1"),m_port));
    return s_ports.value(type);
}

bool JPortService::passLoginHash(JPortSocket& socket)
{
    QElapsedTimer t;
    JCryproRecorder cr;
    t.start();
    m_plh=-1;
    while(t.elapsed()<1000)
    {
        switch(m_plh)
        {
        case 1:
            return true;
            break;
        case 0:
            return false;
            break;
        case -1:
            if(cr.getUserId()==-1 || cr.getCrypro().isEmpty())
            {
                qDebug()<<"JPortService::passLoginHash : have not record the login hash . can not request id list!";
                return false;
            }
            socket.sendCrypro(cr.getUserId(),cr.getCrypro());
            m_plh=-2;
            break;
        case -2:
            break;
        }

        QCoreApplication::processEvents();
    }
    return false;
}

void JPortService::on_socket_rcvPassLoginHash(bool plh)
{
    qDebug()<<"JPortService::on_socket_rcvPassLoginHash : "<<plh;
    m_plh=plh;
}

void JPortService::on_socket_rcvServerPort(quint16 port)
{
    m_port=port;
}

SHost JPortService::getServerPort(EServerType type)const
{
    return s_ports.value(type);
}
