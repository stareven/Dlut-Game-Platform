#include "jclientnetworkdataprocessorbase.h"

JClientNetworkDataProcessorBase::JClientNetworkDataProcessorBase(QObject *parent) :
    JNetworkDataProcessorBase(parent)
{
    m_socket=NULL;
}
