#include "sqlitecreater.h"

#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDir>

#include <QSqlError>
#include <QDebug>

SQLiteCreater::SQLiteCreater(QWidget *parent, QString _dbName) :
	DatabaseCreater(parent),
	dbName(_dbName)
{
	if (dbName != "_for_checker_only") {
		dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);
		db = new QSqlDatabase;
		*db = QSqlDatabase::addDatabase("QSQLITE", "sqlite");
	} else {
		db = NULL;
		dgpdbIni = NULL;
	}
}

SQLiteCreater::~SQLiteCreater() {
	if (db) {
		if (db->isOpen()) {
			qDebug() << "database closed";
			db->close();
		}
		delete db;
		db = NULL;
		QSqlDatabase::removeDatabase("sqlite");
	}
	if (dgpdbIni) {
		delete dgpdbIni;
		dgpdbIni = NULL;
	}
}

bool SQLiteCreater::checkName(QString name) {
	if (name.isEmpty()) return false;
	foreach(QChar ch, name) {
		if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || (ch == '_') || (ch == '.')) continue;
		return false;
	}
	return true;
}

bool SQLiteCreater::exec() {
	if (finalCheck() && confirmOverwrite() && doDrop() && doCreate()) {
		showConclusion();
		return true;
	} else {
		return false;
	}
}

bool SQLiteCreater::finalCheck() {
	return finalCheckDbName();
}

bool SQLiteCreater::finalCheckDbName() {
	if (!checkName(dbName)) {
		QMessageBox::warning(this, tr("Unavailable Name"),
							 tr("The database name should not be empty\n"
								"and contains only:\n\n"
								"	1.  Lowercase letter\n"
								"	2.  Number\n"
								"	3.  Underline\n"
								"	4.  Dot"),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	return true;
}

bool SQLiteCreater::confirmOverwrite() {
	return confirmOverwriteDb() && confirmOverwriteIni();
}

bool SQLiteCreater::confirmOverwriteDb() {
	if (QDir::current().exists(dbName)) {
		int yes = QMessageBox::warning(this, tr("Overwrite the Database"),
									   tr("A database named \"%1\" already exists.  Do you want to replace it?\n"
										  "Replacing it will overwrite its contents.")
									   .arg(dbName),
									   QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (yes == QMessageBox::Yes)
			return true;
		else
			return false;
	} else {
		return true;
	}
}

bool SQLiteCreater::confirmOverwriteIni() {
	if (!dgpdbIni->isWritable()) {
		QMessageBox::warning(this, tr("Permission Denied"),
							 tr("Unable to write \"%1\"\n"
								"You do not have the permissions necessary to save the file.")
							 .arg(dgpdbIni->fileName()),
							 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}
	if (!dgpdbIni->allKeys().empty()) {
		int yes = QMessageBox::warning(this, tr("Confirm Overwrite Database configuration"),
									   tr("\"%1\" already exists.  Do you want to replace it?\n"
										  "Replacing it will overwrite its contents.")
									   .arg(dgpdbIni->fileName()),
									   QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (yes != QMessageBox::Yes) {
			qDebug() << "A File named \"dgpdb.ini\" already exist.";
			return false;
		} else {
			qDebug() << "Replace the exist file";
			return true;
		}
	} else {
		qDebug() << "not exist";
		//nothing...
		return true;
	}
}

bool SQLiteCreater::doDrop() {
	return dropDb() && dropIni();
}

bool SQLiteCreater::dropDb() {
	if (QDir::current().exists(dbName)) {
		if (QDir::current().remove(dbName)) return true;
		else {
			QMessageBox::critical(this, tr("Overwrite Database Error"),
								  tr("Unable to overwrite \"%1\"\n"
									 "You do not have the permissions necessary to remove the file.")
								  .arg(QDir::current().absoluteFilePath(dbName)),
								  QMessageBox::Ok, QMessageBox::Ok);
			return false;
		}
	} else {
		return false;
	}
}

bool SQLiteCreater::dropIni() {
	dgpdbIni->clear();
	return true;
}

bool SQLiteCreater::doCreate() {
	return createDb() && createIni();
}

bool SQLiteCreater::createDb() {
	//create database
	db->setDatabaseName(dbName);
	if (db->open()) {
		qDebug() << "sqlite open/create succ";
	} else {
		qDebug() << db->lastError().text();
		qDebug() << "sqlite open/create fail";
		return false;
	}
	QSqlQuery *query = new QSqlQuery(*db);

	//create loginingo table
	if (query->exec("CREATE TABLE logininfo(\n"
					"user_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
					"user_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"passwd VARCHAR(50) NOT NULL,"
					"roles INTEGER NOT NULL DEFAULT '0')"))
	{
		qDebug() << "create logininfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create logininfo exec fail";
		return false;
	}

	//create userinfo table
	if (query->exec("CREATE TABLE userinfo(\n"
					"user_id INTEGER PRIMARY KEY,\n"
					"nickname VARCHAR(50),\n"
					"org TEXT)"))
	{
		qDebug() << "create userinfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create userinfo exec fail";
		return false;
	}

	//create serverinfo table
	if (query->exec("CREATE TABLE serverinfo(\n"
					"server_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
					"server_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"runner_id INTEGER,\n"
					"host_addr VARCHAR(255),\n"
					"host_port INTEGER)"))
	{
		qDebug() << "create serverinfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create serverinfo exec fail";
		return false;
	}

	//create gameinfo table
	if (query->exec("CREATE TABLE gameinfo(\n"
					"game_id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
					"game_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"version INTEGER,\n"
					"author_id INTEGER,\n"
					"runner_id INTEGER,\n"
					"server_id INTEGER,\n"
					"download_url VARCHAR(255),\n"
					"intro TEXT)"))
	{
		qDebug() << "create gameinfo succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create gameinfo exec fail";
		return false;
	}

	//set AUTOINCREMENT = 1001 of logininfo
	if (query->exec("INSERT INTO SQLITE_SEQUENCE\n"
					"VALUES('logininfo', '1000')"))
	{
		qDebug() << "set AUTOINCREMENT exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "set AUTOINCREMENT exec fail";
		return false;
	}

	return true;
}

bool SQLiteCreater::createIni() {
	dgpdbIni->beginGroup("SQLite");
	dgpdbIni->setValue("database", dbName);
	dgpdbIni->endGroup();
	dgpdbIni->sync();
	return true;
}

void SQLiteCreater::showConclusion() {
	dgpdbIni->beginGroup("SQLite");
	QMessageBox::information(this, tr("Conclusion"),
							 tr("The MySQL database \"%1\" and the profile \"%2\" have been created successfully!\n"
								"The profile should be put into the same directory with the Mainserver.")
							 .arg(dgpdbIni->value("database").toString())
							 .arg(dgpdbIni->fileName()),
							 QMessageBox::Ok, QMessageBox::Ok);
	dgpdbIni->endGroup();
}
