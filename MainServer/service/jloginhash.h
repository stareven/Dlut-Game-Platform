#ifndef JLOGINHASH_H
#define JLOGINHASH_H

#include <QMap>

#include "global/jglobal.h"

class JLoginHash
{
public:
	// 0 if success , 1 if multi the same id
	JCode add(JID userid,const QByteArray& extra);
	QByteArray get(JID userid)const;
	// 0 if success , 1 if no such user
	JCode del(JID userid);
	// 0 if success , 1 if no such user , 2 if crypro not same
	JCode check(JID userid,const QByteArray& crypro)const;
private:
	static QMap<JID,QByteArray> s_data;
};

#endif // JLOGINHASH_H
