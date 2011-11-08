#ifndef JABSTRACTLOGINDB_H
#define JABSTRACTLOGINDB_H

#include <QObject>

#include "Global/Global"

class JAbstractLoginDB : public QObject
{
public:
	explicit JAbstractLoginDB(QObject *parent = 0);
	virtual JID checkLoginName(const QString& loginname)=0;
	virtual bool checkPasswd(JID,const QString& passwd)=0;
	virtual bool checkRole(JID userId,JID roleId)=0;
	virtual QString getLoginName(JID userId)=0;
	virtual QString getPassword(JID userId)=0;
};

#endif // JABSTRACTLOGINDB_H
