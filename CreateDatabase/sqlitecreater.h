#ifndef SQLITECREATER_H
#define SQLITECREATER_H

#include "databasecreater.h"

class SQLiteCreater : public DatabaseCreater
{
    Q_OBJECT
public:
	explicit SQLiteCreater(QWidget *parent = 0,
						   QString _dbName = "_for_checker_only");
	virtual ~SQLiteCreater();

	// reimplement, contains [_.0-9a-z]
	virtual bool checkName(QString name);

	virtual bool exec();	// execute creating operation

private:
	QString dbName;

	// main structure
	virtual bool finalCheck();
	virtual bool confirmOverwrite();
	virtual bool doDrop();				// drop old database & configuration if exist
	virtual bool doCreate();			// create new database & configuration
	virtual void showConclusion();

	// finalCheck helpers
	bool finalCheckDbName();

	// confirmOverwrite helpers
	bool confirmOverwriteDb();
	bool confirmOverwriteIni();

	//  doDrop helpers
	bool dropIni();
	bool dropDb();

	// doCreate helpers
	bool createDb();
	bool createIni();
};

#endif // SQLITECREATER_H
