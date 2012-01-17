#include "jsocketbase.h"

#include <QTcpSocket>

#include "jnetworkdataprocessorbase.h"
#include "../global/jcodeerror.h"
#include "../global/shost.h"
#include "jsession.h"
#include "jsocketstrategy.h"

/*!
    \class JSocketBase jsocketbase.h <Socket/JSocketBase>
    \ingroup socket
    \brief 套接字基类

    处理基本的数据接收、发送、错误等。 \n
    主要的函数是on_socket_readyRead()。
*/

/*!
    \fn JSocketBase::disconnected()
    \brief 连接断开
*/

/*!
    \fn JSocketBase::error(JCode errorCode )
    \brief 发生错误

    \a errorCode 表示错误类型
*/

/*!
    \brief 构造函数

    JSocketBase对象内部会管理一个QTcpSocket对象。
*/
JSocketBase::JSocketBase(QTcpSocket* socket,QObject* parent)
    :QObject(parent),
    m_socket(socket)
{
    m_type=-1;
	m_size=0;
	m_session = new JSession(this);
	m_socketStrategy=NULL;
	connect(m_socket,SIGNAL(readyRead()),SLOT(on_socket_readyRead()));
	connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(on_socket_error(QAbstractSocket::SocketError)));
	connect(m_socket,SIGNAL(disconnected()),SIGNAL(disconnected()));
}

/*!
    \brief 注册网络数据处理器

    详情参见on_socket_readyRead()
*/
JCode JSocketBase::registerProcessor(JNetworkDataProcessorBase* processor){
	m_processors.insert(processor->getProcessorType(),processor);
    return 0;
}

/*!
    \brief 发送数据
    
    \a type 协议类型。
    \a data 数据内容。
    
    \retval 0 成功。
    \retval 1 socket未连接。
    \retval 2 socket不可写。
*/
JCode JSocketBase::sendData(JType type,const QByteArray& data){
    if(m_socket->state()!=QAbstractSocket::ConnectedState){
        return 1;
    }
    if(!m_socket->isWritable()){
        return 2;
    }
    qint32 size=data.size();
    QDataStream outsocketstream(m_socket);
    outsocketstream<<type;
    outsocketstream<<size;
    m_socket->write(data);
    return 0;
}

/*!
    \brief 关闭连接
*/
void JSocketBase::closeConnect()
{
	m_socket->disconnectFromHost();
}

/*!
    \brief 发起连接
*/
void JSocketBase::connectToServer(const SHost& host)
{
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

/*!
    \brief 获得当前的socket状态
*/
QAbstractSocket::SocketState JSocketBase::socketState () const{
    return m_socket->state();
}

/*!
    \brief 获得session对象

    session对象记录了连接中的某些信息，
    例如用户ID等。
*/
JSession* JSocketBase::getSession()
{
	return m_session;
}

/*!
    \brief 获得当前正在处理的数据的协议类型
*/
JType JSocketBase::getType()const
{
	return m_type;
}

/*!
    \brief 设置 SocketStrategy 对象

    这个对象会在 Processor 对象处理之前进行验证，
    若验证不通过，则不会继续处理。
*/
void JSocketBase::setSocketStrategy(JSocketStrategy* strategy)
{
	m_socketStrategy = strategy;
}

/*!
    \brief 获得 SocketStrategy 对象
*/
JSocketStrategy* JSocketBase::getSocketStrategy()const
{
	return m_socketStrategy;
}

/*!
    \brief 处理数据

    数据开头是2字节的协议类型和4字节的数据长度，\n
    分别是 JType 类型和 qint32 类型。\n
    之后是数据内容。\n

    首先交给 JSocketStrategy 对象认证，\n
    认证通过后交给 JNetworkDataProcessorBase 对象处理。
*/
void JSocketBase::on_socket_readyRead(){
    while(m_socket->bytesAvailable()>0)
    {
        if(m_size>0)
        {
            QByteArray readdata=m_socket->read(m_size-m_data.size());
            m_data+=readdata;
            if(m_data.size()==m_size)
            {
                JNetworkDataProcessorBase* process=m_processors.value(m_type);
				if(process){
					JSocketStrategy *strategy=getSocketStrategy();
					if(NULL == strategy || strategy->filterBeforeProcess(this)){
						process->process(m_data);
					}
				}else{
					qDebug()<<"JSocketBase::on_socket_readyRead : no such type"<<m_type;
				}
                m_data.clear();
                m_size=0;
				m_type=-1;
            }
        }else if(m_socket->bytesAvailable()>=(qint64)(sizeof(m_type)+sizeof(m_size))){
            QDataStream stream(m_socket);
            stream>>m_type;
            stream>>m_size;
        }
    }
}

void JSocketBase::on_socket_error(QAbstractSocket::SocketError socketError)
{
	qDebug()<<metaObject()->className()<<m_socket->errorString();
	emit error(ENetworkError | socketError);
}
