#include "jsqlserverinfodb.h"

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

/*
bool initDatabase(QSqlDatabase *db) {
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	db->addDatabase("SQL");
	db->setHostName("localhost");
	db->setDatabaseName("dgpdb");
	db->setUserName("dgproot");
	db->setPassword("dgproot");
	if (db->open()) {
		db->exec("SET NAMES 'latin1'");
		return true;
	} else
		return false;
}
*/

JSQLServerInfoDB::JSQLServerInfoDB(QSqlDatabase *dgpDB, QObject *parent) :
	JAbstractServerInfoDB(parent), serverInfoDB(dgpDB)
{
	qDebug() << "+ JSQLSerInfoDB constructed";
//	if (!connectCount++) {
//		QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//		QTextCodec::setCodecForCStrings(codec);
//		QTextCodec::setCodecForTr(codec);

//		serverInfoDB = new QSqlDatabase;
//		//	serverInfoDB->addDatabase("QSQL");
//		*serverInfoDB = QSqlDatabase::addDatabase("QSQL", "serverInfoDB");
//		serverInfoDB->setHostName("localhost");
//		serverInfoDB->setDatabaseName("dgpdb");
//		serverInfoDB->setUserName("dgproot");
//		serverInfoDB->setPassword("dgproot");
//		if (serverInfoDB->open()) {
//			qDebug() << "serverInfoDB is open!";
//		} else
//			qDebug() << "serverInfoDB fail...";
//		serverInfoDB->exec("SET NAMES 'latin1'");
//	} else {
//		//nothing...
//	}
}

//JSQLServerInfoDB::~JSQLServerInfoDB() {
//	if (!--connectCount) {
//		serverInfoDB->close();
//		delete serverInfoDB;
//	} else {
//		//nothing...
//	}
//}

JServerInfo JSQLServerInfoDB::getServerInfoById(JID ID) {
	qDebug() << "+ getServerInfoById";
	QSqlQuery *serverInfoQuery = new QSqlQuery(*serverInfoDB);
	if (serverInfoQuery->prepare("SELECT server_name,	\n"
								 "runner_id,			\n"
								 "host_addr,			\n"
								 "host_port				\n"
								 "FROM serverinfo		\n"
								 "WHERE server_id = :serverID"))
		qDebug() << "getServerInfoById prepare succ";
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "getServerInfoById prepare fail";
	}
	serverInfoQuery->bindValue(":serverID", ID);
	if (serverInfoQuery->exec())
		qDebug() << "getServerInfoById exec succ";
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "getServerInfoId exec fail";
	}
	if (serverInfoQuery->next())
		return JServerInfo(ID,
						   serverInfoQuery->value(0).toString(),
						   serverInfoQuery->value(1).toInt(),
						   SHost(QHostAddress(serverInfoQuery->value(2).toString()),
								 serverInfoQuery->value(3).toInt())
						   );
	else
		return JServerInfo();
}

JCode JSQLServerInfoDB::updateServerInfo(const JServerInfo &serverInfo) {
	qDebug() << "+ updateServerInfo";
	QSqlQuery *serverInfoQuery = new QSqlQuery(*serverInfoDB);
	if (serverInfoQuery->prepare("UPDATE serverinfo SET				\n"
									"server_name = :serverName,	\n"
									"runner_id = :runnerID,		\n"
									"host_addr = :hostAddr,		\n"
									"host_port = :hostPort		\n"
								 "WHERE server_id = :serverID"))
		qDebug() << "updateServerInfo prepare succ";
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "updateServerInfo prepare fail";
	}
	serverInfoQuery->bindValue(":serverName", serverInfo.getName());
	serverInfoQuery->bindValue(":runnerID", serverInfo.getRunner());
	serverInfoQuery->bindValue(":hostAddr", serverInfo.getHost().m_address.toString());
	serverInfoQuery->bindValue(":hostPort", serverInfo.getHost().m_port);
	serverInfoQuery->bindValue(":serverID", serverInfo.getServerId());
	if (serverInfoQuery->exec()) {
		qDebug() << "updateServerInfo exec succ";
		return 0;
	}
	else {
		qDebug() << serverInfoQuery->lastError().databaseText();
		qDebug() << "updateServerInfo exec fail";
		return -1;
	}
}
