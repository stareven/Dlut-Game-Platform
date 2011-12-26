#ifndef DATABASECREATER_H
#define DATABASECREATER_H

#include <QWidget>

class QSettings;
class QSqlDatabase;

class DatabaseCreater : public QWidget
{
	Q_OBJECT
public:
	explicit DatabaseCreater(QWidget *parent = 0);
	virtual ~DatabaseCreater();

	virtual bool exec() = 0;	// execute creating operation

	// checker
	virtual bool checkName(QString name);
	virtual bool checkPwdLength(QString passwd);
	virtual bool checkConfirmPwd(QString userPwd, QString confirmPwd);

protected:
	QSettings *dgpdbIni;		// database configuration
	QSqlDatabase *db;			// database connection

private:
	// main structure
	virtual bool finalCheck() = 0;
	virtual bool confirmOverwrite() = 0;
	virtual bool doDrop() = 0;				// drop old database & configuration if exist
	virtual bool doCreate() = 0;			// create new database & configuration
	virtual void showConclusion() = 0;

};

#endif // DATABASECREATER_H
