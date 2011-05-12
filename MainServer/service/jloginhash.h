#ifndef JLOGINHASH_H
#define JLOGINHASH_H

#include "jglobal.h"

namespace JLoginHash
{
    class JAdd
    {
    public:
	/// 0 if success , 1 if multi the same id
	JCode add(JID userid,const QByteArray& extra);
    };

    class JGet
    {
    public:
	QByteArray get(JID userid)const;
    };

    class JDelete
    {
    public:
	/// 0 if success , 1 if no such user
	JCode del(JID userid);
    };

    class JCheck
    {
    public:
	/// 0 if success , 1 if no such user , 2 if crypro not same
	JCode check(JID userid,const QByteArray& crypro)const;
    };
};

#endif // JLOGINHASH_H
