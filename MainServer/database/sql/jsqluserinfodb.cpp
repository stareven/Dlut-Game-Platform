#include "jsqluserinfodb.h"

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

JSQLUserInfoDB::JSQLUserInfoDB(QSqlDatabase *dgpDB, QObject *parent) :
	JAbstractUserInfoDB(parent), userInfoDB(dgpDB)
{
	qDebug() << "+ JSQLUserInfo constructed";
//	if (!connectCount++) {
//		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//		QTextCodec::setCodecForCStrings(codec);
//		QTextCodec::setCodecForTr(codec);

//		userInfoDB = new QSqlDatabase;
//		//	userInfoDB->addDatabase("QSQL");
//		*userInfoDB = QSqlDatabase::addDatabase("QSQL", "userInfoDB");
//		userInfoDB->setHostName("localhost");
//		userInfoDB->setDatabaseName("dgpdb");
//		userInfoDB->setUserName("dgproot");
//		userInfoDB->setPassword("dgproot");
//		if (userInfoDB->open()) {
//			qDebug() << "userInfoDB is open";
//		} else
//			qDebug() << "userInfoDB fail";
//		userInfoDB->exec("SET NAMES 'latin1'");
//	} else {
//		//nothing...
//	}
}

//JSQLUserInfoDB::~JSQLUserInfoDB() {
//	if (!--connectCunt) {
//		userInfoDB->close();
//		delete userInfoDB;
//	} else {
//		//nothing...
//	}
//}

JUserInfo JSQLUserInfoDB::getUserInfoById(JID userID) {
	qDebug() << "+ getUserInfoById";
	testUserinfoExist(userID);
	QSqlQuery *userInfoQuery = new QSqlQuery(*userInfoDB);
	if (userInfoQuery->prepare("SELECT nickname, org FROM userinfo	\n"
							   "WHERE user_id = :userID"))
		qDebug() << "getUserInfoById prepare succ";
	else {
		qDebug() << userInfoQuery->lastError().databaseText();
		qDebug() << "getUserInfoById prepare fail";
	}
	userInfoQuery->bindValue(":userID", userID);
	if (userInfoQuery->exec())
		qDebug() << "getUserInfoById exec succ";
	else {
		qDebug() << userInfoQuery->lastError().databaseText();
		qDebug() << "getUserInfoById exec fail";
	}
	if (userInfoQuery->next())
		return JUserInfo(userID,
						 userInfoQuery->value(0).toString(),
						 userInfoQuery->value(1).toString()
						 );
	else
		return JUserInfo();
}

JCode JSQLUserInfoDB::updateUserInfo(const JUserInfo &userInfo) {
	qDebug() << "+ updateUserInfo";
	testUserinfoExist(userInfo.getUserId());
	QSqlQuery *userInfoQuery = new QSqlQuery(*userInfoDB);
	if (userInfoQuery->prepare("UPDATE userinfo	SET			\n"
									"nickname = :nickname,	\n"
									"org = :org				\n"
							   "WHERE user_id = :userID"))
		qDebug() << "updateUserInfo prepare succ";
	else {
		qDebug() << userInfoQuery->lastError().databaseText();
		qDebug() << "updateUserInfo prepare fail";
	}
	userInfoQuery->bindValue(":nickname", userInfo.getNickname());
	userInfoQuery->bindValue(":org", userInfo.getOrganization());
	userInfoQuery->bindValue(":userID", userInfo.getUserId());
	if (userInfoQuery->exec()) {
		qDebug() << "updateUserInfo exec succ";
		return 0;
	} else {
		qDebug() << userInfoQuery->lastError().databaseText();
		qDebug() << "updateUserInfo exec fail";
		return -1;
	}
}

void JSQLUserInfoDB::testUserinfoExist(const JID userID) {
	qDebug() << "~~ test userinfo exist";
	QSqlQuery *userInfoQuery = new QSqlQuery(*userInfoDB);
	if (userInfoQuery->prepare("SELECT * from userinfo\n"
							   "WHERE user_id = :userID"))
	{
		qDebug() << "test userinfo exist prepare succ";
	} else {
		qDebug() << userInfoQuery->lastError().text();
		qDebug() << "test userinfo exist prepare fail";
		return ;
	}
	userInfoQuery->bindValue(":userID", userID);
	if (userInfoQuery->exec()) {
		qDebug() << "test userinfo exist exec succ";
	} else {
		qDebug() << userInfoQuery->lastError().text();
		qDebug() << "test userinfo exist exec fail";
		return ;
	}

	// if not exists ,insert one empty userinfo...
	if (userInfoQuery->next()) return ;

	if (userInfoQuery->prepare("INSERT INTO userinfo(user_id) VALUES(:userID)")) {
		qDebug() << "insert userinfo prepare succ";
	} else {
		qDebug() << userInfoQuery->lastError().text();
		qDebug() << "insert userinfo prepare fail";
		return ;
	}
	userInfoQuery->bindValue(":userID", userID);
	if (userInfoQuery->exec()) {
		qDebug() << "insert userinfo exec succ";
	} else {
		qDebug() << userInfoQuery->lastError().text();
		qDebug() << "insert userinfo exec fail";
		return ;
	}
}
