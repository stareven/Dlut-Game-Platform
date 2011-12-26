#ifndef MYSQLCREATER_H
#define MYSQLCREATER_H

#include "databasecreater.h"

class MySQLCreater : public DatabaseCreater
{
    Q_OBJECT
public:
	explicit MySQLCreater(QWidget *parent = 0,
						  QString _dbName = "_for_checker_only",
						  QString _userName = "",
						  QString _userPwd = "",
						  QString _confirmPwd = "");
	virtual ~MySQLCreater();

	virtual bool exec();	// execute creating operation

private:
	QString dbName;
	QString userName;
	QString userPwd;
	QString confirmPwd;

	// main structure
	virtual bool finalCheck();
	virtual bool confirmOverwrite();
	virtual bool doDrop();				// drop old database & configuration if exist
	virtual bool doCreate();			// create new database & configuration
	virtual void showConclusion();

	// finalCheck helpers
	bool finalCheckDbName();
	bool finalCheckUserName();
	bool finalCheckPwd();

	// try to connect to MySQL
	bool connectToDbAsRoot();

	// confirmOverwrite helpers
	bool confirmOverwriteDb();
	bool confirmOverwriteIni();

	// doDrop helpers
	bool dropIni();
	bool dropDb();

	// doCreate helpers
	bool createDb();
	bool createIni();
};

#endif // MYSQLCREATER_H
