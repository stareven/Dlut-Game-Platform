#include "mysqlcreater.h"

#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QDir>

#include <QSqlError>
#include <QDebug>

MySQLCreater::~MySQLCreater() {
	if (db->isOpen()) {
		qDebug() << "database close";
		db->close();
	}
	delete db;
}

MySQLCreater::MySQLCreater(QWidget *parent) :
	DatabaseCreater(parent)
{
//	dgpdbIni = new QSettings("dgpdb.ini", QSettings::IniFormat);
	db = new QSqlDatabase;
	*db = QSqlDatabase::addDatabase("QMYSQL", "mysql");
	db->setUserName("root");

	dbNameLabel = new QLabel(tr("&Database Name:"), this);
	dbNameLabel->setAlignment(Qt::AlignRight);
	dbNameEdit = new QLineEdit(this);
	dbNameEdit->setMaxLength(16);
	dbNameLabel->setBuddy(dbNameEdit);
	dbNameStatus = new QLabel(tr("OK!"), this);
	connect(dbNameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkDbName(QString)));

	userNameLabel = new QLabel(tr("User &Name:"), this);
	userNameLabel->setAlignment(Qt::AlignRight);
	userNameEdit = new QLineEdit(this);
	userNameEdit->setMaxLength(16);
	userNameLabel->setBuddy(userNameEdit);
	userNameStatus = new QLabel(tr("OK!"), this);
	connect(userNameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkUserName(QString)));

	userPwdLabel = new QLabel(tr("User &Password:"), this);
	userPwdLabel->setAlignment(Qt::AlignRight);
	userPwdEdit = new QLineEdit(this);
	userPwdEdit->setMaxLength(16);
	userPwdEdit->setEchoMode(QLineEdit::Password);
	userPwdLabel->setBuddy(userPwdEdit);
	userPwdStatus = new QLabel(tr("ERROR!"), this);
	connect(userPwdEdit, SIGNAL(textChanged(QString)), this, SLOT(checkUserPwd(QString)));

	confirmPwdLabel = new QLabel(tr("Con&firm Password:"), this);
	confirmPwdLabel->setAlignment(Qt::AlignRight);
	confirmPwdEdit = new QLineEdit(this);
	confirmPwdEdit->setMaxLength(16);
	confirmPwdEdit->setEchoMode(QLineEdit::Password);
	confirmPwdLabel->setBuddy(confirmPwdEdit);
	confirmPwdStatus = new QLabel(tr("ERROR!"), this);
	connect(confirmPwdEdit, SIGNAL(textChanged(QString)), this, SLOT(checkConfirmPwd(QString)));

	reset();

	resetBtn = new QPushButton(tr("&Reset"), this);
	connect(resetBtn, SIGNAL(clicked()), this, SLOT(reset()));

	createBtn = new QPushButton(tr("&Create"), this);
	connect(createBtn, SIGNAL(clicked()), this, SLOT(create()));

	QVBoxLayout *mainLayout = new QVBoxLayout;

	QGridLayout *editLayout = new QGridLayout;
	editLayout->addWidget(dbNameLabel, 0, 0);
	editLayout->addWidget(dbNameEdit, 0, 1);
	editLayout->addWidget(dbNameStatus, 0, 2);
	editLayout->addWidget(userNameLabel, 1, 0);
	editLayout->addWidget(userNameEdit, 1, 1);
	editLayout->addWidget(userNameStatus, 1, 2);
	editLayout->addWidget(userPwdLabel, 2, 0);
	editLayout->addWidget(userPwdEdit, 2, 1);
	editLayout->addWidget(userPwdStatus, 2, 2);
	editLayout->addWidget(confirmPwdLabel, 3, 0);
	editLayout->addWidget(confirmPwdEdit, 3, 1);
	editLayout->addWidget(confirmPwdStatus, 3, 2);

	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addWidget(resetBtn);
	btnLayout->addStretch();
	btnLayout->addWidget(createBtn);

	mainLayout->addLayout(editLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(btnLayout);

	setLayout(mainLayout);

	//fix the size
	confirmPwdEdit->setFixedWidth(confirmPwdEdit->sizeHint().width());
	confirmPwdStatus->setFixedWidth(confirmPwdStatus->sizeHint().width());
	setFixedSize(sizeHint());
}

void MySQLCreater::reset() {
//	dgpdbIni->beginGroup("MySQL");
//	if (dgpdbIni->contains("database"))
//		dbNameEdit->setText(dgpdbIni->value("database").toString());
//	else
		dbNameEdit->setText("dgpdb");
//	if (dgpdbIni->contains("user"))
//		userNameEdit->setText(dgpdbIni->value("user").toString());
//	else
		userNameEdit->setText("dgproot");
//	dgpdbIni->endGroup();

	userPwdEdit->setText("");
	confirmPwdEdit->setText("");
}

void MySQLCreater::checkUserName(QString name) {
	if (doCheckName(name))
		userNameStatus->setText(tr("OK!"));
	else
		userNameStatus->setText(tr("ERROR!"));
}

void MySQLCreater::checkUserPwd(QString passwd) {
	if (doCheckPwdLength(passwd))
		userPwdStatus->setText(tr("OK!"));
	else
		userPwdStatus->setText(tr("ERROR!"));
	checkConfirmPwd(confirmPwdEdit->text());
}

void MySQLCreater::checkConfirmPwd(QString passwd) {
	if (doCheckPwdLength(passwd) && doCheckConfirmPwd(passwd))
		confirmPwdStatus->setText(tr("OK!"));
	else
		confirmPwdStatus->setText(tr("ERROR!"));
}

bool MySQLCreater::doCheckPwdLength(QString passwd) {
	return passwd.length() >= 6;
}

bool MySQLCreater::doCheckConfirmPwd(QString passwd) {
	return passwd == userPwdEdit->text();
}

void MySQLCreater::create() {
	if (!finalCheck()) return ;
	if (doDrop() && doCreate()) showConclusion();
}

bool MySQLCreater::finalCheck() {
	if (!finalCheckDbName() || !finalCheckUserName() || !finalCheckPwd()) return false;
	if (!tryRootPwd()) return false;
	if (!confirmOverwrite()) return false;
	return true;
}

bool MySQLCreater::finalCheckDbName() {
	if (!doCheckName(dbNameEdit->text())) {
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
	if (!doCheckName(userNameEdit->text())) {
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
	if (!doCheckPwdLength(userPwdEdit->text())) {
		QMessageBox::warning(this, tr("Unavailable User Password"),
							 tr("The user password is too short!\n"
								"The length of the user password should not be less than 6."),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	if (!doCheckConfirmPwd(confirmPwdEdit->text())) {
		QMessageBox::warning(this, tr("Confirm User Password"),
							 tr("\"Confirm Password\" is diffrent from \"User Passeord\"!\n"
								"\"Confirm Password\" should be the same as \"User Passeord\"!"),
							 QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}
	return true;
}

bool MySQLCreater::tryRootPwd() {
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
	query->bindValue(":dbName", dbNameEdit->text());
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

bool MySQLCreater::confirmOverwriteIni() {
	qDebug() << dgpdbIni->fileName();
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
					.arg(dbNameEdit->text())))
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
					.arg(dbNameEdit->text()))) {
		qDebug() << "create db exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "create db exec fail";
		return false;
	}
	if (query->exec(QString("GRANT ALL ON %1.* TO %2@localhost IDENTIFIED BY '%3'")
					.arg(dbNameEdit->text())
					.arg(userNameEdit->text())
					.arg(userPwdEdit->text()))) {
		qDebug() << "grant exec succ";
	} else {
		qDebug() << query->lastError().text();
		qDebug() << "grant exec fail";
		return false;
	}
	if (query->exec(QString("USE %1")
					.arg(dbNameEdit->text())))
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
	dgpdbIni->setValue("database", dbNameEdit->text());
	dgpdbIni->setValue("user", userNameEdit->text());
	dgpdbIni->setValue("password", userPwdEdit->text());
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
