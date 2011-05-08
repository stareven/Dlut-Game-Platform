#include "jcryprorecorder.h"

//#include <QDebug>

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
    //qDebug()<<"JCryproRecorder::setCrypro : crypro="<<crypro.toHex().toUpper();
    s_crypro=crypro;
}

const QByteArray& JCryproRecorder::getCrypro()const
{
    return s_crypro;
}

void JCryproRecorder::setUserId(JID id)
{
    //qDebug()<<"JCryproRecorder::setCrypro : userid="<<id;
    s_userid=id;
}

JID JCryproRecorder::getUserId()const
{
    return s_userid;
}
