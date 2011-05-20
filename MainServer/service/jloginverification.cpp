#include "jloginverification.h"

#include <QString>
#include <QCryptographicHash>

#include "database/jabslogindb.h"

JLoginVerification::JLoginVerification()
{
    m_userid=-1;
}

/// return 0 if succeed
/// return 1 if no such user
/// return 2 if password wrong
/// return 3 if no such role
ELogin JLoginVerification::verification(const QString& loginname,const QString& passwd,const JID& role)
{
    JAbsLoginDB logindb;
    JID id=logindb.checkLoginName(loginname);
    if(id<0) return EL_NO_SUCH_USER;
    if(!logindb.checkPasswd(id,passwd)) return EL_PASSWD_WRONG;
    if(!logindb.checkRole(id,role)) return EL_NO_SUCH_ROLE;
    m_userid=id;
    QByteArray data;
    data.append(loginname);
    data.append(passwd);
//    JLoginHash::JAdd add;
//    add.add(m_userid,data);
//    JLoginHash::JGet get;
//    m_crypro=get.get(m_userid);
    return EL_SUCCESS;

//    struct SLoginUser
//    {
//        QString m_loginname;
//        QString m_passwd;
//        JRole m_role;
//    };
//
//    static const int NUM_USER=3;
//    static const SLoginUser loginusers[NUM_USER]={
//        {"elephant","acm",ROLE_GAMEPLAYER},
//        {"jdmd","jdmd",ROLE_ADMIN | ROLE_ROOT },
//        {"lixiaopang","lxp",ROLE_GAMEDESIGNER | ROLE_ADMIN }
//    };
////    44095add9f53307994169faf8fa68cc4
////    bd1fc747fc61eeda95ca0ba81b99dc02
////    344607dc3af16feccee386f46844572c
//
//    for(int i=0;i<NUM_USER;++i)
//    {
//        if(loginusers[i].m_loginname==loginname)
//        {
//            if(loginusers[i].m_passwd==passwd)
//            {
//                if(loginusers[i].m_role & role)
//                {
//                    m_userid=i;
////                    QCryptographicHash cryprohash(QCryptographicHash::Md5);
////                    cryprohash.addData(loginname.toAscii());
////                    cryprohash.addData(passwd.toAscii());
////                    m_crypro=cryprohash.result();
////                    qDebug("%s",m_crypro.toHex().toUpper().data());
//                    JUserLoginCrypro& ulc=JUserLoginCrypro::getInstance();
//                    QByteArray data;
//                    data.append(loginname);
//                    data.append(passwd);
//                    ulc.addUserLogin(m_userid,data);
//                    return 0;
//                }else{
//                    return 3;
//                }
//            }else{
//                return 2;
//            }
//        }
//    }
//    return 1;
}

/// return userid if succeed , -1 if failed
JID JLoginVerification::JLoginVerification::getUserId()const
{
    return m_userid;
}

// return crypto if succeed , QByteArray() if failed
//QByteArray JLoginVerification::getCrypro()const
//{
//    return m_crypro;
//}
