#include "jsocketbase.h"

#include <QTcpSocket>

#include "jnetworkdataprocessorbase.h"

JSocketBase::JSocketBase(QTcpSocket* socket,QObject* parent)
    :QObject(parent),
    m_socket(socket)
{
    m_type=-1;
    m_size=0;
	connect(m_socket,SIGNAL(readyRead()),SLOT(on_socket_readyRead()));
	connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(on_socket_error(QAbstractSocket::SocketError)));
	connect(m_socket,SIGNAL(connected()),SLOT(on_socket_connected()));
}

JCode JSocketBase::registerProcessor(JNetworkDataProcessorBase* processor){
	m_processors.insert(processor->getProcessorType(),processor);
    return 0;
}

/*!
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

QAbstractSocket::SocketState JSocketBase::socketState () const{
    return m_socket->state();
}

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
					process->process(m_data);
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

void JSocketBase::on_socket_error(QAbstractSocket::SocketError)
{
	qDebug()<<metaObject()->className()<<m_socket->errorString();
}

void JSocketBase::on_socket_connected()
{
}
