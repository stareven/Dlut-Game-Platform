#include "jloginhash.h"

#include <QCryptographicHash>
#include <QTime>

QMap<JID,QByteArray> JLoginHash::s_data;

// 0 if success , 1 if multi the same id
JCode JLoginHash::add(JID userid,const QByteArray& extra)
{
	if(s_data.contains(userid)) return 1;
	QCryptographicHash ch(QCryptographicHash::Md5);
	ch.addData(extra);
	ch.addData(QTime::currentTime().toString().toAscii());
	s_data.insert(userid,ch.result().left(8));
	return 0;
}

QByteArray JLoginHash::get(JID userid)const
{
	return s_data.value(userid);
}

// 0 if success , 1 if no such user
JCode JLoginHash::del(JID userid)
{
	if(!s_data.contains(userid)) return 1;
	s_data.remove(userid);
	return 0;
}

// 0 if success , 1 if no such user , 2 if crypro not same
JCode JLoginHash::check(JID userid,
						const QByteArray& crypro)const
{
	if(!s_data.contains(userid)) return 1;
	if(s_data.value(userid)!=crypro) return 2;
	return 0;
}
