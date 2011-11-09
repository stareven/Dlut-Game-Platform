#include "jclientloginprocessor.h"

#include "jclientsocketbase.h"
#include "jclientsession.h"

JClientLoginProcessor::JClientLoginProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JClientLoginProcessor* JClientLoginProcessor::getInstance(){
    static JClientLoginProcessor* instance=NULL;
    if(NULL==instance){
        JClientSocketBase* socket=JClientSocketBase::getInstance();
		JClientSession* session = JClientSession::getInstance();
		instance=new JClientLoginProcessor(session,socket);
		socket->registerProcessor(instance);
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
	QByteArray loginhashcode;
    stream>>code;
    if(code==0)
    {
        stream>>m_userid;
		stream>>loginhashcode;
		getSession()->setUserId(m_userid);
		getSession()->setLoginHashCode(loginhashcode);
    }
    emit loginCode(code);
}

JType JClientLoginProcessor::getProcessorType()const{
    return EPI_LOGIN;
}
