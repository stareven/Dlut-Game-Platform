#include "service/jcryprorecorder.h"

QByteArray JCryproRecorder::s_crypro;
JID JCryproRecorder::s_userid;

JCryproRecorder::JCryproRecorder()
{
}

void JCryproRecorder::set(const QByteArray& crypro,JID id)
{
    setCrypro(crypro);
    setUserId(id);
}

void JCryproRecorder::setCrypro(const QByteArray& crypro)
{
    s_crypro=crypro;
}

const QByteArray& JCryproRecorder::getCrypro()const
{
    return s_crypro;
}

void JCryproRecorder::setUserId(JID id)
{
    s_userid=id;
}

JID JCryproRecorder::getUserId()const
{
    return s_userid;
}
