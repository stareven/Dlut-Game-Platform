#ifndef JHEAD_H
#define JHEAD_H

#include "jglobal.h"

/*!
    \file jhead.h
    \ingroup global
    \brief 定义了 NetworkData::JHead 结构体
*/

namespace NetworkData{
    struct JHead{
        JType m_type;
        qint16 m_category;
        JID m_id;

        explicit JHead(JID id=-1,JType type=-1,qint16 category=-1);
        bool operator<(const JHead& head)const;
    };
    enum EInformationType{
        EIT_UserInfo,
        EIT_GameInfo,
        EIT_ServerInfo,
    };
}
bool operator==(const NetworkData::JHead&,const NetworkData::JHead&);
uint qHash(const NetworkData::JHead&);

class QDataStream;
QDataStream& operator<<(QDataStream&,const NetworkData::JHead&);
QDataStream& operator>>(QDataStream&,NetworkData::JHead&);

#endif // JHEAD_H
