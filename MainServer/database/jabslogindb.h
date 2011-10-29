#ifndef JABSLOGINDB_H
#define JABSLOGINDB_H

#include <QObject>

#include "Global/Global"

class JAbsLoginDB : public QObject
{
public:
	JAbsLoginDB(QObject *parent = 0);
	virtual JID checkLoginName(const QString& loginname)=0;
	virtual bool checkPasswd(JID,const QString& passwd)=0;
	virtual bool checkRole(JID,JID)=0;
};

#endif // JABSLOGINDB_H
