#include "maindialog.h"
#include "mysqlcreater.h"
#include "sqlitecreater.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
	checker = NULL;

	//dbTypeGroup
//	qDebug() << "++ dbTypeGroup ++";
	dbTypeGroup = new QGroupBox(tr("Database Type"), this);
	mysqlBtn = new QRadioButton(tr("&MySQL"), this);
	connect(mysqlBtn, SIGNAL(clicked()), this, SLOT(convertToMySQLInterface()));
	sqliteBtn = new QRadioButton(tr("SQ&Lite"), this);
	connect(sqliteBtn, SIGNAL(clicked()), this, SLOT(convertToSQLiteInterface()));
	QHBoxLayout *dbTypeLayout = new QHBoxLayout;
	dbTypeLayout->addWidget(mysqlBtn);
	dbTypeLayout->addWidget(sqliteBtn);
	dbTypeGroup->setLayout(dbTypeLayout);

	//edit line layout
//	qDebug() << "++ edit line layout ++";
	dbNameLabel = new QLabel(tr("&Database Name:"), this);
	dbNameLabel->setAlignment(Qt::AlignRight);
	dbNameEdit = new QLineEdit(this);
	dbNameEdit->setMaxLength(16);
	dbNameLabel->setBuddy(dbNameEdit);
	dbNameStatus = new QLabel(tr("ERROR!"), this);
	connect(dbNameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkDbName(QString)));

	userNameLabel = new QLabel(tr("User &Name:"), this);
	userNameLabel->setAlignment(Qt::AlignRight);
	userNameEdit = new QLineEdit(this);
	userNameEdit->setMaxLength(16);
	userNameLabel->setBuddy(userNameEdit);
	userNameStatus = new QLabel(tr("ERROR!"), this);
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
	//fix the width
	dbNameLabel->setFixedWidth(confirmPwdLabel->sizeHint().width());
	dbNameEdit->setFixedWidth(dbNameEdit->sizeHint().width());
	dbNameStatus->setFixedWidth(dbNameStatus->sizeHint().width());

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

	//button layout
//	qDebug() << "++ button layout ++";
	resetBtn = new QPushButton(tr("&Reset"), this);
	connect(resetBtn, SIGNAL(clicked()), this, SLOT(reset()));

	createBtn = new QPushButton(tr("&Create"), this);
	connect(createBtn, SIGNAL(clicked()), this, SLOT(create()));

	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->addWidget(resetBtn);
	btnLayout->addStretch();
	btnLayout->addWidget(createBtn);

	//set default interface
//	qDebug() << "++ default interface ++";
	mysqlBtn->setChecked(true);
	convertToMySQLInterface();

	//main layout
//	qDebug() << "++ main layout ++";
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(dbTypeGroup);
	mainLayout->addLayout(editLayout);
	mainLayout->addStretch();
	mainLayout->addLayout(btnLayout);

//	qDebug() << "++ set layout ++" ;
	setLayout(mainLayout);
	setFixedSize(sizeHint());
	setWindowTitle(tr("Create Database"));
}

void MainDialog::convertToMySQLInterface() {
//	qDebug() << "++ convert to MySQL interface ++";
	//interface
//	qDebug() << "+ set interface +";
	dbNameLabel->show();
	dbNameEdit->show();
	dbNameStatus->show();
	userNameLabel->show();
	userNameEdit->show();
	userNameStatus->show();
	userPwdLabel->show();
	userPwdEdit->show();
	userPwdStatus->show();
	confirmPwdLabel->show();
	confirmPwdEdit->show();
	confirmPwdStatus->show();

	//checker
//	qDebug() << "+ redefine checker +";
	if (checker) delete checker;
	checker = new MySQLCreater(this);

	//reset edit lines
//	qDebug() << "+ reset edit lines +";
	reset();
}

void MainDialog::convertToSQLiteInterface() {
//	qDebug() << "++ convert to SQLite interface ++";
	//interface
//	qDebug() << "+ set interface +";
	dbNameLabel->show();
	dbNameEdit->show();
	dbNameStatus->show();
	userNameLabel->hide();
	userNameEdit->hide();
	userNameStatus->hide();
	userPwdLabel->hide();
	userPwdEdit->hide();
	userPwdStatus->hide();
	confirmPwdLabel->hide();
	confirmPwdEdit->hide();
	confirmPwdStatus->hide();

	//checker
//	qDebug() << "+ redefine checker +";
	if (checker) delete checker;
	checker = new SQLiteCreater(this);

	//reset edit lines
//	qDebug() << "+ reset edit lines +";
	reset();
}

void MainDialog::checkDbName(QString name) {
	if (checker->checkName(name))
		dbNameStatus->setText(tr("OK!"));
	else
		dbNameStatus->setText(tr("ERROR!"));
}

void MainDialog::checkUserName(QString name) {
	if (checker->checkName(name))
		userNameStatus->setText(tr("OK!"));
	else
		userNameStatus->setText(tr("ERROR!"));
}

void MainDialog::checkUserPwd(QString passwd) {
	if (checker->checkPwdLength(passwd))
		userPwdStatus->setText(tr("OK!"));
	else
		userPwdStatus->setText(tr("ERROR!"));

	checkConfirmPwd(confirmPwdEdit->text());
}

void MainDialog::checkConfirmPwd(QString passwd) {
	if (checker->checkConfirmPwd(userPwdEdit->text(), passwd))
		confirmPwdStatus->setText(tr("OK!"));
	else
		confirmPwdStatus->setText(tr("ERROR!"));
}

void MainDialog::reset() {
	if (mysqlBtn->isChecked()) {
		dbNameEdit->setText("dgpdb");
		userNameEdit->setText("dgproot");
		userPwdEdit->setText("");
		confirmPwdEdit->setText("");
		return ;
	}
	if (sqliteBtn->isChecked()) {
		dbNameEdit->setText("dgp.db");
		return ;
	}
	qDebug() << "++ in MainDialog reset ++";
	qDebug() << "no db type checked";
}

void MainDialog::create() {
	DatabaseCreater *creater = NULL;
	if (mysqlBtn->isChecked())
		creater = new MySQLCreater(this,
								   dbNameEdit->text(),
								   userNameEdit->text(),
								   userPwdEdit->text(),
								   confirmPwdEdit->text());
	if (sqliteBtn->isChecked())
		creater = new SQLiteCreater(this, dbNameEdit->text());
	if (!creater) {
		qDebug() << "++ in MainDialog create ++";
		qDebug() << "creater not bind";
		return ;
	}

	if (creater->exec()) {
		qDebug() << "database & dgpdb.ini create succ";
	} else {
		qDebug() << "database & dgpdb.ini create fail";
	}

	delete creater;
	creater = NULL;
}
