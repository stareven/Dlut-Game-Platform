#include "jsqllogindb.h"

#include <Global/Global>
#include <Global/Login>
#include <Global/Register>

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>


JSQLLoginDB::JSQLLoginDB(QSqlDatabase *dgpDB, QObject *parent) :
	JAbstractLoginDB(parent), loginDB(dgpDB)
{
	qDebug() << "+ JSQLLoginDB constructed";
}


JID JSQLLoginDB::checkLoginName(const QString &loginName) {
	qDebug() << "+ checkLoginName";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	loginQuery->prepare("SELECT user_id FROM logininfo	\n"
						"WHERE user_name = :loginName");
	loginQuery->bindValue(":loginName", loginName);
	loginQuery->exec();
	if (loginQuery->next())
		return loginQuery->value(0).toInt();
	else return -1;
}

bool JSQLLoginDB::checkPasswd(JID userID, const QString &passwd) {
	qDebug() << "+ checkPasswd";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	loginQuery->prepare("SELECT passwd FROM logininfo	\n"
						"WHERE user_id = :userID");
	loginQuery->bindValue(":userID", userID);
	loginQuery->exec();

	if (loginQuery->next()) {
		qDebug() << "pwd in MySQL:" << loginQuery->value(0).toString();
		qDebug() << "my pwd:" << passwd;
		return loginQuery->value(0).toString() == passwd;
	} else {
		return false;
	}
	//return (loginQuery->next() &&
		//	loginQuery->value(0).toString() == passwd);
}

bool JSQLLoginDB::checkRole(JID userID, JID roleID) {
	qDebug() << "+ checkRole";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	loginQuery->prepare("SELECT roles FROM logininfo	\n"
						"WHERE user_id = :userID");
	loginQuery->bindValue(":userID", userID);
	loginQuery->exec();
	return (loginQuery->next() &&
			loginQuery->value(0).toInt() & (1 << roleID));
}

QString JSQLLoginDB::getLoginName(JID userID) {
	qDebug() << "+ getLoginName";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	if (loginQuery->prepare("SELECT user_name FROM logininfo	\n"
							"WHERE user_id = :userID")) {
		qDebug() << "getLoginName prepare successfully";
	} else
		qDebug() << "getLoginName prepare fail";
	loginQuery->bindValue(":userID", userID);

	//without wrong userID checking...
	if (loginQuery->exec()) {
//	if (loginQuery->exec("SELECT user_name FROM logininfo WHERE user_id = 1001")) {
		qDebug() << "getLoginName execute successfully!";
	} else {
		qDebug() << loginQuery->lastError().databaseText();
		qDebug() << "getLoginName execute fail";
	}
	if (loginQuery->next())
		return loginQuery->value(0).toString();
	else
		return loginQuery->lastError().databaseText();
}

QString JSQLLoginDB::getPassword(JID userID) {
	qDebug() << "+ getPassword";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
//	loginQuery->prepare("SELECT passwd FROM logininfo	\n"
//						"WHERE user_id = :userID");
	if (loginQuery->prepare("SELECT passwd FROM logininfo	\n"
							"WHERE user_id = :userID"))
		qDebug() << "getPassword prepare succ";
	else qDebug() << "getPassword prepare fail";
	loginQuery-> bindValue(":userID", userID);
	//without wrong userID checking...
//	loginQuery->exec();
	if (loginQuery->exec())
		qDebug() << "getPassword exec succ";
	else qDebug() << "getPassword exec fail";
	qDebug() << "before next";
	if (loginQuery->next()) {
		qDebug() << "getPassword has next";
		return loginQuery->value(0).toString();
	} else
		return loginQuery->lastError().databaseText();
}

JCode JSQLLoginDB::addLoginUser(const QString &loginName, const QString &passwd) {
	qDebug() << "+ addLoginUser";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	if (loginQuery->prepare("INSERT INTO logininfo			\n"
						"(user_name, passwd, roles)			\n"
						"VALUES(:loginName, :passwd, :roles)"))
		qDebug() << "addLoginUser prepare succ";
	else qDebug() << "addLoginUser prepare fail";
	loginQuery->bindValue(":loginName", loginName);
	loginQuery->bindValue(":passwd", passwd);
	loginQuery->bindValue(":roles", 1 << ROLE_GAMEPLAYER);
	if (loginQuery->exec()) {
		qDebug() << "addLoginUser exec succ" ;
		return 0;
	}
	else {
		qDebug() << loginQuery->lastError();
		return ER_UserIdFull;//wrong description
	}
}

JRoleCombination JSQLLoginDB::JSQLLoginDB::getRoleCombination(JID userID) {
	qDebug() << "+ getRoleCombination";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	loginQuery->prepare("SELECT roles FROM logininfo	\n"
						"WHERE user_id = :userID");
	loginQuery->bindValue(":userID", userID);
	loginQuery->exec();
	if (loginQuery->next()) {
		return loginQuery->value(0).toInt();
	}
	return -1;
}

void JSQLLoginDB::setRoleCombination(JID userID, JRoleCombination roles) {
	qDebug() << "+ setRoleCombination";
	QSqlQuery *loginQuery = new QSqlQuery(*loginDB);
	if (loginQuery->prepare("UPDATE logininfo		\n"
							"SET roles = :roles		\n"
							"WHERE user_id = :userID"))
		qDebug() << "setRoleCombination prepare succ";
	else qDebug() << "setRoleCombination prepare fail";
	loginQuery->bindValue(":roles", roles);
	loginQuery->bindValue(":user_ID", userID);
	//without error checking...
	if (loginQuery->exec()) {
		qDebug() << "setRoleCombination exec succ";
	} else {
		qDebug() << loginQuery->lastError().databaseText();
		qDebug() << "setRoleCombination exec fail";
	}
}
