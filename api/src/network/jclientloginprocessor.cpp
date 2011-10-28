#include "jclientloginprocessor.h"

#include "jclientsocketbase.h"

JClientLoginProcessor::JClientLoginProcessor(JClientSocketBase *socket) :
	JClientNetworkDataProcessorBase(socket)
{
}

JClientLoginProcessor* JClientLoginProcessor::getInstance(){
    static JClientLoginProcessor* instance=NULL;
    if(NULL==instance){
        JClientSocketBase* socket=JClientSocketBase::getInstance();
		instance=new JClientLoginProcessor(socket);
		socket->registerProcessor(instance->getProcessorType(),instance);
    }
    return instance;
}

void JClientLoginProcessor::login(const QString& loginname,
                                  const QString& passwd,
                                  ERole role){
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<(JID)role;
	JCode code=sendData(data);
	if(0!=code){
		qDebug()<<"JClientLoginProcessor::login : sendData failed:"<<code;
	}
}

void JClientLoginProcessor::process(const QByteArray& data){
    QDataStream stream(data);
    JCode code;
    stream>>code;
    if(code==0)
    {
        stream>>m_userid;
    }
    emit loginCode(code);
}

JType JClientLoginProcessor::getProcessorType()const{
    return EPI_LOGIN;
}
