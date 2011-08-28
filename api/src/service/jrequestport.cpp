#include "service/jrequestport.h"

#include <QCoreApplication>

#include "network/jrequestportsocket.h"
#include "service/jloginhashcoderecorder.h"
#include "global/jelapsedtimer.h"

QMap<EServerType,SHost> JRequestPort::s_ports;

/*!
	\file jrequestport.h
	\brief 定义了 JRequestPort 类
*/

/*!
	\class JRequestPort jrequestport.h "service/jrequestport.h"
	\ingroup client
	\brief 获得各个服务的端口

	MainServer上，每个服务单独使用一个端口。\n
	此外，提供两个服务查询所有服务的端口列表。\n
	其中，没有服务提供FreePort。FreePort只能从平台运维者处人为地获得。\n
	并且，通常平台运维者发布的MainServer的端口是它的FreePort服务的端口。\n
	请求Login和SecretPort服务不需要Login hash confirm，这两个服务的端口由FreePort服务提供。\n
	剩下的服务需要Login hash confirm，由SecretPort服务提供。\n
	关于Login hash confirm和Login hash code，参见 JLoginHashCodeRecorder 的文档。\n

	\warning 这个类的代码写的很烂，接口也很混乱。

	\sa JLoginHashCodeRecorder
*/

/*!
	\brief 构造函数。
*/
JRequestPort::JRequestPort(QObject *parent) :
    QObject(parent)
{
}

/*!
	\brief 直接设置某个服务的端口。

	由于获得各个服务的端口最终都需要首先知道FreePort的端口，所以至少需要知道MainServer的FreePort的端口，然后通过这个函数设置进来。
*/
void JRequestPort::setServerPort(EServerType type,const SHost& host)
{
    s_ports.insert(type,host);
}

/*!
	\brief 请求\a type 服务的端口。

	如果曾经请求过，无论是否是在同一个JRequestPort 的实例中，它都会被记录下来。\n
	这样当再次请求这个服务的端口的时候，这个函数会直接返回本地保存的该服务的端口，而不会重新向服务器发起请求。
*/
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

/*!
	\brief 以可读的字符串形式返回错误信息。
*/
const QString& JRequestPort::getError()const
{
	return m_error;
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
            socket.sendLoginHashCode(lhcr.getUserId(),lhcr.getCode());
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
