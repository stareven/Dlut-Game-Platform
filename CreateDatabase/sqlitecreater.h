#ifndef SQLITECREATER_H
#define SQLITECREATER_H

#include "databasecreater.h"
class QLabel;
class QLineEdit;
class QPushButton;
class QLayout;

class SQLiteCreater : public DatabaseCreater
{
    Q_OBJECT
public:
	explicit SQLiteCreater(QWidget *parent = 0);
	~SQLiteCreater();

private slots:
	virtual void reset();
	virtual void create();

private:
	virtual bool doCheckName(QString name);
	virtual bool finalCheck();
	bool finalCheckDbName();
	virtual bool confirmOverwrite();
	bool confirmOverwriteDb();
	bool confirmOverwriteIni();
	bool doDrop();
	bool dropIni();
	bool dropDb();
	virtual bool doCreate();
	bool createDb();
	bool createIni();
	virtual void showConclusion();
};

#endif // SQLITECREATER_H
