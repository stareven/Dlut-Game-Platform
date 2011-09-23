#include "jclientloginprocessor.h"

#include "jclientsocketbase.h"

JClientLoginProcessor::JClientLoginProcessor(QObject *parent) :
    JClientNetworkDataProcessorBase(parent)
{
}

JClientLoginProcessor* JClientLoginProcessor::getInstance(){
    static JClientLoginProcessor* instance=NULL;
    if(NULL==instance){
        JClientSocketBase* socket=JClientSocketBase::getInstance();
        instance=new JClientLoginProcessor(socket);
        socket->registerProcessor(instance->getProcessorId(),instance);
    }
    return instance;
}

void JClientLoginProcessor::login(const QString& loginname,const QString& passwd,const JID& role){
    QByteArray data;
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream<<loginname<<passwd;
    stream<<role;
    JClientSocketBase::getInstance()->sendData(getProcessorId(),data);
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

JID JClientLoginProcessor::getProcessorId()const{
    return EPI_LOGIN;
}
