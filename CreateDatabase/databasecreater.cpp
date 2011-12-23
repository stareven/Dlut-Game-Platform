#include "databasecreater.h"

#include <QLabel>
#include <QSqlDatabase>
#include <QSettings>
#include <QDebug>

QSettings* DatabaseCreater::dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);

DatabaseCreater::DatabaseCreater(QWidget *parent) :
	QWidget(parent)
{
//	dgpdbIni->setIniCodec("UTF-8");
}


void DatabaseCreater::checkDbName(QString name) {
	if (doCheckName(name))
		dbNameStatus->setText(tr("OK!"));
	else
		dbNameStatus->setText(tr("ERROR!"));
}

bool DatabaseCreater::doCheckName(QString name) {
	if (name.isEmpty()) return false;
	foreach(QChar ch, name) {
		if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || (ch =='_')) continue;
		return false;
	}
	return true;
}
