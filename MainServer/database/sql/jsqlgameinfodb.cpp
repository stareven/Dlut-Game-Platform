#include "jsqlgameinfodb.h"

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

JSQLGameInfoDB::JSQLGameInfoDB(QSqlDatabase *dgpDB, QObject *parent) :
	JAbstractGameInfoDB(parent), gameInfoDB(dgpDB)
{
	qDebug() << "+ JSQLGameInfoDB constructed";
}

JGameInfo JSQLGameInfoDB::getGameInfoById(JID ID) {
	qDebug() << "+ getGameInfoById" <<endl;
	QSqlQuery *gameInfoQuery = new QSqlQuery(*gameInfoDB);
	if (gameInfoQuery->prepare("SELECT game_name,		\n"
									"version,			\n"
									"author_id,			\n"
									"runner_id,			\n"
									"intro,				\n"
									"server_id,			\n"
									"download_url		\n"
							   "FROM gameinfo			\n"
							   "WHERE game_id = :gameID"))
		qDebug() << "getGameInfoById prepare succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameInfoById prepare fail";
	}
	gameInfoQuery->bindValue(":gameID", ID);
	if (gameInfoQuery->exec())
		qDebug() << "getGameInfoById exec succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameInfoById exec fail";
	}
	//without gameID checking...
	if (gameInfoQuery->next())
		return JGameInfo(ID,
						 gameInfoQuery->value(0).toString(),
						 JVersion((quint32)gameInfoQuery->value(1).toInt()),
						 gameInfoQuery->value(2).toInt(),
						 gameInfoQuery->value(3).toInt(),
						 gameInfoQuery->value(4).toString(),
						 gameInfoQuery->value(5).toInt(),
						 QUrl(gameInfoQuery->value(6).toString())
						 );
	else
		return JGameInfo();
}

JGameList JSQLGameInfoDB::getGameList() {
	qDebug() << "+ getGameList";
	QSqlQuery *gameInfoQuery = new QSqlQuery(*gameInfoDB);
	if (gameInfoQuery->exec("SELECT game_id, game_name FROM gameinfo"))
		qDebug() << "getGameList exec succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "getGameList exec fail";
	}
	JGameList gameList;
	while (gameInfoQuery->next()) {
		gameList.insert(gameInfoQuery->value(0).toInt(),
						gameInfoQuery->value(1).toString()
						);
	}
	return gameList;
}

JCode JSQLGameInfoDB::updateGameInfo(const JGameInfo &gameInfo) {
	qDebug() << "+ updateGameInfo";
	QSqlQuery *gameInfoQuery = new QSqlQuery(*gameInfoDB);
	qDebug() << gameInfo.getGameId()
			 << gameInfo.getName()
			 << gameInfo.getVersion().getData()
			 << gameInfo.getAuthor()
			 << gameInfo.getRunner()
			 << gameInfo.getIntroduction()
			 << gameInfo.getServerId()
			 << gameInfo.getDownloadUrl().toString();
	if (gameInfoQuery->prepare("UPDATE gameinfo	SET				\n"
									"game_name = :gameName,		\n"
									"version = :version,		\n"
									"author_id = :authorID,		\n"
									"runner_id = :runnerID,		\n"
									"intro = :introdution,		\n"
									"server_id = :serverID,		\n"
									"download_url = :downUrl	\n"
							   "WHERE game_id = :gameID"))
		qDebug() << "updateGameInfo prepare succ";
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		qDebug() << "upDataGameInfo prepare fail";
	}
	gameInfoQuery->bindValue(":gameName", gameInfo.getName());
	gameInfoQuery->bindValue(":version", gameInfo.getVersion().getData());
	gameInfoQuery->bindValue(":authorID", gameInfo.getGameId());
	gameInfoQuery->bindValue(":runnerID", gameInfo.getRunner());
	gameInfoQuery->bindValue(":introdution", gameInfo.getIntroduction());
	gameInfoQuery->bindValue(":serverID", gameInfo.getServerId());
	gameInfoQuery->bindValue(":downUrl", gameInfo.getDownloadUrl().toString());
	gameInfoQuery->bindValue(":gameID", gameInfo.getGameId());
	if (gameInfoQuery->exec()) {
		qDebug() << "updateGameInfo exec succ";
		return 0;
	}
	else {
		qDebug() << gameInfoQuery->lastError().databaseText();
		return -1;//undefined
	}
}
