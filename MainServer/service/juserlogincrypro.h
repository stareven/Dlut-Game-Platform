#ifndef JUSERLOGINCRYPRO_H
#define JUSERLOGINCRYPRO_H

#include "global/jglobal.h"
#include "jloginhash.h"

#include <QMap>
#include <QByteArray>

class JUserLoginCrypro
{
private:
    JUserLoginCrypro();
    JUserLoginCrypro(const JUserLoginCrypro&);
    static JUserLoginCrypro s_userlogincrypro;

    QMap<JID,QByteArray> m_data;

protected:
    static JUserLoginCrypro& getInstance();

    /// 0 if success , 1 if multi the same id
    JCode addUserLogin(JID userid,const QByteArray& extra);

    QByteArray getCrypro(JID userid)const;

    /// 0 if success , 1 if no such user
    JCode delUserLogin(JID userid);
    
    /// 0 if success , 1 if no such user , 2 if crypro not same
    JCode checkUserLogin(JID userid,const QByteArray& crypro)const;

    friend class JLoginHash::JAdd;
    friend class JLoginHash::JGet;
    friend class JLoginHash::JDelete;
    friend class JLoginHash::JCheck;
};

#endif // JUSERLOGINCRYPRO_H
