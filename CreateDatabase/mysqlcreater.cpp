#include "mysqlcreater.h"

#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>

#include <QSqlError>
#include <QDebug>

MySQLCreater::MySQLCreater(QWidget *parent,
						   QString _dbName, QString _userName, QString _userPwd, QString _confirmPwd) :
	DatabaseCreater(parent),
	dbName(_dbName), userName(_userName), userPwd(_userPwd), confirmPwd(_confirmPwd)
{
//	qDebug() << "++ construct MySQLCreater ++";
	if (dbName != "_for_checker_only") {
//		qDebug() << "+ construct a real creater +";
		dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);
		db = new QSqlDatabase;
		*db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
	} else {
		db = NULL;
		dgpdbIni = NULL;
//		qDebug() << "+ construct only a checker +";
	}
//	qDebug() << "++ construct MySQLCreater end ++";
}

MySQLCreater::~MySQLCreater() {
//	qDebug() << "++ destoy MySQLCreater ++";
	if (db) {
//		qDebug() << "+ db not null +";
		if (db->isOpen()) {
			qDebug() << "database closed";
			db->close();
		}
		delete db;
		db = NULL;
		QSqlDatabase::removeDatabase("mysql");
	} else {
//		qDebug() << "+ db is null +";
	}
	if (dgpdbIni) {
//		qDebug() << "+ dgpdbIni not null +";
		delete dgpdbIni;
		dgpdbIni = NULL;
	} else {
//		qDebug() << "+ dgpdbIni is null +";
	}
//	qDebug() << "++ destroy end ++";
}

bool MySQLCreater::exec() {
	if (finalCheck() && connectToDbAsRoot() && confirmOverwrite() && doDrop() && doCreate()) {
		showConclusion();
		return true;
	} else {
		return false;
	}
}

bool MySQLCreater::finalCheck() {
	return finalCheckDbName() && finalCheckUserName() && finalCheckPwd();
}

bool MySQLCreater::finalCheckDbName() {
	if (!checkName(dbName)) {
		QMessageBox::warning(this, tr("Unavailable Name"),
							 tr("The database name should not be empty\n"
								"and contains only:\n\n"
								"	1.  Lowercase letter\n"
								"	2.  Number\n"
								"	3.  Underline"),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	return true;
}

bool MySQLCreater::finalCheckUserName() {
	if (!checkName(userName)) {
		QMessageBox::warning(this, tr("Unavailable Name"),
							 tr("The user name should not be empty\n"
								"and contains only:\n\n"
								"	1.  Lowercase letter\n"
								"	2.  Number\n"
								"	3.  Underline"),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	return true;
}

bool MySQLCreater::finalCheckPwd() {
	if (!checkPwdLength(userPwd)) {
		QMessageBox::warning(this, tr("Unavailable User Password"),
							 tr("The user password is too short!\n"
								"The length of the user password should not be less than 6."),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	if (!checkConfirmPwd(userPwd, confirmPwd)) {
		QMessageBox::warning(this, tr("Confirm User Password"),
							 tr("\"Confirm Password\" is diffrent from \"User Passeord\"!\n"
								"\"Confirm Password\" should be the same as \"User Passeord\"!"),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	return true;
}

bool MySQLCreater::connectToDbAsRoot() {
	db->setUserName("root");
	while (true) {
		bool ok = true;
		QString password = QInputDialog::getText(this, QObject::tr("Connect to MySQL as Root"),
												 QObject::tr("Enter the root password for MySQL:"),
												 QLineEdit::Password, QObject::tr(""), &ok);
		if (!ok) return false;
		db->setPassword(password);
		if (db->open()) {
			qDebug() << "mysql connected";
			return true;
		}
		else {
			qDebug() << db->lastError().databaseText();
			int yes = QMessageBox::warning(this, QObject::tr("Wrong Password"),
										   QObject::tr("The root password for MySQL is WRONG!\n"
													   "Retry?"),
										   QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
			if (yes != QMessageBox::Yes) return false;
		}
	}
}

bool MySQLCreater::confirmOverwrite() {
	if (!confirmOverwriteDb()) return false;
	if (!confirmOverwriteIni()) return false;
	return true;
}

bool MySQLCreater::confirmOverwriteDb() {
	QSqlQuery *query = new QSqlQuery(*db);
	if (query->exec("USE information_schema")) {
		qDebug() << "USE infomation_schema succ";
	} else {
		qDebug() << query->lastError().databaseText();
		qDebug() << "USE infomation_schema fail";
		delete query;
		return false;
	}
	if (query->prepare("SELECT 1 FROM SCHEMATA	\n"
					   "WHERE SCHEMA_NAME = :dbName"))
		qDebug() << "find dbName prepare succ";
	else {
		qDebug() << query->lastError().databaseText();
		qDebug() << "find dbName prepare fail";
		return false;
	}
	query->bindValue(":dbName", dbName);
	if (query->exec()) {
		qDebug() << "find dbName exec succ";
	} else {
		qDebug() << query->lastError().databaseText();
		qDebug() << "find dbName exec fail";
		return false;
	}
	if (query->next()) {
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

bool MySQLCreater::confirmOverwriteIni() {
//	qDebug() << dgpdbIni->fileName();
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

bool MySQLCreater::doDrop() {
	return dropDb() && dropIni();
}

bool MySQLCreater::dropDb() {
	QSqlQuery *query = new QSqlQuery(*db);
	if (query->exec(QString("DROP DATABASE IF EXISTS %1")
					.arg(dbName)))
	{
		qDebug() << "drop succ";
		return true;
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "drop fail";
		return false;
	}
}

bool MySQLCreater::dropIni() {
	dgpdbIni->clear();
	return true;
}

bool MySQLCreater::doCreate() {
	return createDb() && createIni();
}

bool MySQLCreater::createDb() {
	QSqlQuery *query = new QSqlQuery(*db);
	if (query->exec(QString("CREATE DATABASE %1")
					.arg(dbName))) {
		qDebug() << "create db exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create db exec fail";
		return false;
	}
	if (query->exec(QString("GRANT ALL ON %1.* TO %2@localhost IDENTIFIED BY '%3'")
					.arg(dbName)
					.arg(userName)
					.arg(userPwd))) {
		qDebug() << "grant exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "grant exec fail";
		return false;
	}
	if (query->exec(QString("USE %1")
					.arg(dbName)))
	{
		qDebug() << "use db exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "use db exec fail";
		return false;
	}

	if (query->exec("CREATE TABLE logininfo(\n"
					"user_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
					"user_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"passwd VARCHAR(50) NOT NULL,\n"
					"roles TINYINT UNSIGNED NOT NULL DEFAULT '0')"))
	{
		qDebug() << "create logininfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create logininfo exec fail";
		return false;
	}

	if (query->exec("ALTER TABLE logininfo AUTO_INCREMENT=1001")) {
		qDebug() << "alter logininfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "alter logininfo exec fail";
		return false;
	}

	if (query->exec("CREATE TABLE userinfo(\n"
					"user_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
					"nickname VARCHAR(50),\n"
					"org TEXT)"))
	{
		qDebug() << "create userinfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create userinfo exec fail";
		return false;
	}

	if (query->exec("CREATE TABLE serverinfo(\n"
					"server_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
					"server_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"runner_id INT UNSIGNED,\n"
					"host_addr VARCHAR(255),\n"
					"host_port SMALLINT UNSIGNED)"))
	{
		qDebug() << "create serverinfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create serverinfo exec fail";
		return false;
	}

	if (query->exec("CREATE TABLE gameinfo(\n"
					"game_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
					"game_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"version INT UNSIGNED,\n"
					"author_id INT UNSIGNED,\n"
					"runner_id INT UNSIGNED,\n"
					"server_id INT UNSIGNED,\n"
					"download_url VARCHAR(255),\n"
					"intro TEXT)"))
	{
		qDebug() << "create gameinfo succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create gameinfo exec fail";
		return false;
	}

	return true;
}

bool MySQLCreater::createIni() {
	dgpdbIni->beginGroup("MySQL");
	dgpdbIni->setValue("database", dbName);
	dgpdbIni->setValue("user", userName);
	dgpdbIni->setValue("password", userPwd);
	dgpdbIni->endGroup();
	dgpdbIni->sync();
	return true;
}

void MySQLCreater::showConclusion() {
	dgpdbIni->beginGroup("MySQL");
	QMessageBox::information(this, tr("Conclusion"),
							 tr("The MySQL database \"%1\" and the profile \"%2\" have been created successfully!\n"
								"The profile should be put into the same directory with the Mainserver.")
							 .arg(dgpdbIni->value("database").toString())
							 .arg(dgpdbIni->fileName()),
							 QMessageBox::Ok, QMessageBox::Ok);
	dgpdbIni->endGroup();
}
