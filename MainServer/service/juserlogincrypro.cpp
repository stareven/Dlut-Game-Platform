#include "juserlogincrypro.h"

#include <QCryptographicHash>
#include <QTime>

JUserLoginCrypro::JUserLoginCrypro()
{
}

JUserLoginCrypro JUserLoginCrypro::s_userlogincrypro;

//QMap<JID,QByteArray> m_data;

JUserLoginCrypro& JUserLoginCrypro::getInstance()
{
    return s_userlogincrypro;
}

/// 0 if success , 1 if multi the same id
JCode JUserLoginCrypro::addUserLogin(JID userid,const QByteArray& extra)
{
    if(m_data.contains(userid)) return 1;
    QCryptographicHash ch(QCryptographicHash::Md5);
    ch.addData(extra);
    ch.addData(QTime::currentTime().toString().toAscii());
    m_data.insert(userid,ch.result());
    return 0;
}

QByteArray JUserLoginCrypro::getCrypro(JID userid)const
{
    return m_data.value(userid);
}

/// 0 if success , 1 if no such user
JCode JUserLoginCrypro::delUserLogin(JID userid)
{
    if(!m_data.contains(userid)) return 1;
    m_data.remove(userid);
    return 0;
}

/// 0 if success , 1 if no such user , 2 if crypro not same
JCode JUserLoginCrypro::checkUserLogin(JID userid,const QByteArray& crypro)const
{
    if(!m_data.contains(userid)) return 1;
    if(m_data.value(userid)!=crypro) return 2;
    return 0;
}
