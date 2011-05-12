#include "jloginhash.h"

#include "juserlogincrypro.h"

JCode JLoginHash::JAdd::add(JID userid, const QByteArray &extra)
{
    return JUserLoginCrypro::getInstance().addUserLogin(userid,extra);
}

QByteArray JLoginHash::JGet::get(JID userid)const
{
    return JUserLoginCrypro::getInstance().getCrypro(userid);
}

JCode JLoginHash::JDelete::del(JID userid)
{
    return JUserLoginCrypro::getInstance().delUserLogin(userid);
}

JCode JLoginHash::JCheck::check(JID userid,const QByteArray& crypro)const
{
    return JUserLoginCrypro::getInstance().checkUserLogin(userid,crypro);
}
