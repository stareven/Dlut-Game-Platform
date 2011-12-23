#include "sqlitecreater.h"

#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDir>

#include <QSqlError>
#include <QDebug>

SQLiteCreater::~SQLiteCreater() {
	if (db->isOpen()) {
		qDebug() << "database close";
		db->close();
	}
	delete db;
}

SQLiteCreater::SQLiteCreater(QWidget *parent) :
    DatabaseCreater(parent)
{
	dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);
	db = new QSqlDatabase;
	*db = QSqlDatabase::addDatabase("QSQLITE", "sqlite");

	dbNameLabel = new QLabel(tr("&Database Name:"), this);
	dbNameLabel->setAlignment(Qt::AlignRight);
	dbNameEdit = new QLineEdit(this);
	dbNameEdit->setMaxLength(16);
	dbNameEdit->setFixedWidth(dbNameEdit->sizeHint().width());
	dbNameLabel->setBuddy(dbNameEdit);
	dbNameStatus = new QLabel(tr("ERROR!"), this);
	//fix the size
	dbNameStatus->setFixedWidth(dbNameStatus->sizeHint().width());
	dbNameStatus->setText("OK!");
	connect(dbNameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkDbName(QString)));

	reset();

	resetBtn = new QPushButton(tr("&Reset"), this);
	connect(resetBtn, SIGNAL(clicked()), this, SLOT(reset()));

	createBtn = new QPushButton(tr("&Create"), this);
	connect(createBtn, SIGNAL(clicked()), this, SLOT(create()));

	QVBoxLayout *mainLayout = new QVBoxLayout;

	QGridLayout *editLayout  = new QGridLayout;
	editLayout->addWidget(dbNameLabel, 0, 0);
	editLayout->addWidget(dbNameEdit, 0, 1);
	editLayout->addWidget(dbNameStatus, 0, 2);

	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addWidget(resetBtn);
	btnLayout->addStretch();
	btnLayout->addWidget(createBtn);

	mainLayout->addLayout(editLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(btnLayout);

	setLayout(mainLayout);


	//fix the size

	resize(sizeHint());
}

bool SQLiteCreater::doCheckName(QString name) {
	if (name.isEmpty()) return false;
	foreach(QChar ch, name) {
		if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || (ch == '_') || (ch == '.')) continue;
		return false;
	}
	return true;
}

void SQLiteCreater::reset() {
//	dgpdbIni->beginGroup("SQLite");
//	if (dgpdbIni->contains("database"))
//		dbNameEdit->setText(dgpdbIni->value("database").toString());
//	else
		dbNameEdit->setText("dgp.db");
//	dgpdbIni->endGroup();
}

void SQLiteCreater::create() {
	if (!finalCheck()) return ;
	if (doDrop() && doCreate()) showConclusion();
}

bool SQLiteCreater::finalCheck() {
	if (!finalCheckDbName()) return false;
	if (!confirmOverwrite()) return false;
	return true;
}

bool SQLiteCreater::finalCheckDbName() {
	if (!doCheckName(dbNameEdit->text())) {
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
	if (QDir::current().exists(dbNameEdit->text())) {
		int yes = QMessageBox::warning(this, tr("Overwrite the Database"),
									   tr("A database named \"%1\" already exists.  Do you want to replace it?\n"
										  "Replacing it will overwrite its contents.")
									   .arg(dbNameEdit->text()),
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
	if (QDir::current().exists(dbNameEdit->text())) {
		if (QDir::current().remove(dbNameEdit->text())) return true;
		else {
			QMessageBox::critical(this, tr("Overwrite Database Error"),
								  tr("Unable to overwrite \"%1\"\n"
									 "You do not have the permissions necessary to remove the file.")
								  .arg(QDir::current().absoluteFilePath(dbNameEdit->text())),
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
	db->setDatabaseName(dbNameEdit->text());
	if (db->open()) {
		qDebug() << "sqlite open/create succ";
	} else {
		qDebug() << db->lastError().text();
		qDebug() << "sqlite open/create fail";
		return false;
	}
	QSqlQuery *query = new QSqlQuery(*db);

//	if (query->exec(QString("CREATE DATABASE %1")
//					.arg(dbNameEdit->text())))
//	{
//		qDebug() << "create sqlite database exec succ";
//	} else {
//		qDebug() << query->lastError().text();
//		qDebug() << "create sqlite database exec fail";
//		return false;
//	}

	if (query->exec("CREATE TABLE logininfo(\n"
					"user_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
					"user_name VARCHAR(50) NOT NULL UNIQUE,\n"
					"passwd VARCHAR(50) NOT NULL,"
					"roles TINYINT UNSIGNED NOT NULL DEFAULT '0')"))
	{
		qDebug() << "create logininfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create logininfo exec fail";
		return false;
	}

	/*	ERROR
	if (query->exec("ALTER TABLE logininfo AUTO_INCREMENT=1001")) {
		qDebug() << "alter logininfo exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "alter logininfo exec fail";
		return false;
	}
	*/

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

bool SQLiteCreater::createIni() {
	dgpdbIni->beginGroup("SQLite");
	dgpdbIni->setValue("database", dbNameEdit->text());
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
