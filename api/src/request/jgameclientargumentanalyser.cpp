#include "jgameclientargumentanalyser.h"

#include <QStringList>

JGameClientArgumentAnalyser::JGameClientArgumentAnalyser()
{
}

JGameClientArgumentAnalyser* JGameClientArgumentAnalyser::getInstance()
{
    static JGameClientArgumentAnalyser instance;
    return &instance;
}

bool JGameClientArgumentAnalyser::processArgument(const QStringList& arguments)
{
    if(arguments.length()<7){
        return false;
    }
    m_userId=arguments.at(1).toInt();
    QString strcrypro=arguments.at(2);
    m_loginhashcode=QByteArray::fromHex(strcrypro.toAscii());
    QHostAddress ms_addr(arguments.at(3));
    quint16 ms_port(arguments.at(4).toInt());
    m_mainserver = SHost(ms_addr,ms_port);
    m_gameserver = SHost(QHostAddress(arguments.at(5)),arguments.at(6).toInt());
    return true;
}

JID JGameClientArgumentAnalyser::getUserId()const
{
    return m_userId;
}

const QByteArray& JGameClientArgumentAnalyser::getLoginHashCode()const
{
    return m_loginhashcode;
}

const SHost& JGameClientArgumentAnalyser::getMainServer()const
{
    return m_mainserver;
}

const SHost& JGameClientArgumentAnalyser::getGameServer()const
{
    return m_gameserver;
}
