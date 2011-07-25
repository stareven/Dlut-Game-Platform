#include "service/jrequestport.h"

#include <QCoreApplication>

#include "network/jrequestportsocket.h"
#include "service/jloginhashcoderecorder.h"
#include "global/jelapsedtimer.h"

QMap<EServerType,SHost> JRequestPort::s_ports;

JRequestPort::JRequestPort(QObject *parent) :
    QObject(parent)
{
}

void JRequestPort::setServerPort(EServerType type,const SHost& host)
{
    s_ports.insert(type,host);
}

SHost JRequestPort::rqsServerPort(EServerType type)
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
    JRequestPortSocket socket;
	connect(&socket,SIGNAL(SocketError(QString)),SLOT(on_socket_SocketError(QString)));
    SHost host;
    if(isInFree(type))
    {
        host=rqsServerPort(EST_FREEPORT);
    }else{
        host=rqsServerPort(EST_SECRETPORT);
    }
	if(host.isNull()) return SHost();
    socket.connectToHost(host.m_address,host.m_port);
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<1000)
    {
		if(socket.isConnected() || !m_error.isEmpty()) break;
        QCoreApplication::processEvents();
    }
	if(!m_error.isEmpty())
	{
		qDebug()<<m_error;
		return SHost();
	}
    if(!socket.isConnected())
    {
		qDebug()<<"connect time out.1";
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
		if(m_port || !m_error.isEmpty()) break;
        QCoreApplication::processEvents();
    }
	if(!m_error.isEmpty())
	{
		return SHost();
	}
    if(!m_port)
    {
		qDebug()<<"connect time out.2";
        return SHost();
    }
	s_ports.insert(type,SHost(s_ports.value(EST_FREEPORT).m_address,m_port));
    return s_ports.value(type);
}

bool JRequestPort::passLoginHash(JRequestPortSocket& socket)
{
    JElapsedTimer t;
    JLoginHashCodeRecorder lhcr;
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
            if(lhcr.getUserId()==-1 || lhcr.getCode().isEmpty())
            {
                qDebug()<<"JRequestPort::passLoginHash : have not record the login hash . can not request id list!";
                return false;
            }
            socket.sendCrypro(lhcr.getUserId(),lhcr.getCode());
            m_plh=-2;
            break;
        case -2:
            break;
        }

        QCoreApplication::processEvents();
    }
    return false;
}

void JRequestPort::on_socket_rcvPassLoginHash(bool plh)
{
    m_plh=plh;
}

void JRequestPort::on_socket_rcvServerPort(quint16 port)
{
    m_port=port;
}

void JRequestPort::on_socket_SocketError(const QString& error)
{
	m_error=error;
}

SHost JRequestPort::getServerPort(EServerType type)const
{
    return s_ports.value(type);
}

const QString& JRequestPort::getError()const
{
	return m_error;
}
