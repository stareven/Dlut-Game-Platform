#include "databasecreater.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSettings>

DatabaseCreater::DatabaseCreater(QWidget *parent) :
	QWidget(parent)
{
}

DatabaseCreater::~DatabaseCreater() {
//	qDebug() << "++++++ called ~DatabaseCreater ++++++";
	if (db) {
		delete db;
		db = NULL;
	}
	if (dgpdbIni) {
		delete dgpdbIni;
		dgpdbIni = NULL;
	}
}

bool DatabaseCreater::checkName(QString name) {
	if (name.isEmpty()) return false;
	foreach (QChar ch, name) {
		if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || (ch =='_')) continue;
		return false;
	}
	return true;
}

bool DatabaseCreater::checkPwdLength(QString passwd) {
	return passwd.length() >= 6;
}

bool DatabaseCreater::checkConfirmPwd(QString userPwd, QString confirmPwd) {
	return userPwd == confirmPwd;
}
