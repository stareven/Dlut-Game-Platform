#include "jloginhashcodecreator.h"

#include <QCryptographicHash>
#include <QTime>

#include "database/jabstractdatabasefactory.h"
#include "database/jabstractlogindb.h"

JLoginHashCodeCreator::JLoginHashCodeCreator()
{
	m_userId=-1;
}

void JLoginHashCodeCreator::setUserId(JID userId)
{
	m_userId=userId;
}

QByteArray JLoginHashCodeCreator::createLoginHashCode()
{
	QCryptographicHash ch(QCryptographicHash::Md5);
	JAbstractLoginDB* logindb=JAbstractDatabaseFactory::getInstance()->createLoginDB();
	ch.addData(QByteArray::fromHex(logindb->getLoginName(m_userId).toAscii()));
	ch.addData(QByteArray::fromHex(logindb->getPassword(m_userId).toAscii()));
	ch.addData(QTime::currentTime().toString().toAscii());
	return ch.result();
}
