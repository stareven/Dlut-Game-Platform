#include "jclientsocketbase.h"

JClientSocketBase::JClientSocketBase(QTcpSocket* const socket,QObject *parent) :
    JSocketBase(socket,parent)
{
}

JClientSocketBase* JClientSocketBase::getInstance(){
    //配置好各个processor
    static JClientSocketBase* instance=NULL;
    if(NULL==instance){
        //
    }
    return instance;
}
