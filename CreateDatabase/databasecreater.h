#ifndef DATABASECREATER_H
#define DATABASECREATER_H

#include <QWidget>
class QSettings;
class QSqlDatabase;
class QLabel;
class QLineEdit;
class QPushButton;
class QLayout;

class DatabaseCreater : public QWidget
{
	Q_OBJECT
public:
	explicit DatabaseCreater(QWidget *parent = 0);

protected slots:
	virtual void reset() = 0;
	virtual void create() = 0;
	virtual void checkDbName(QString name);

protected:
	static QSettings *dgpdbIni;
	QSqlDatabase *db;
	QLabel *dbNameLabel;
	QLineEdit *dbNameEdit;
	QLabel *dbNameStatus;

	QPushButton *createBtn;
	QPushButton *resetBtn;

	virtual bool doCheckName(QString name);
	virtual bool finalCheck() = 0;
	virtual bool confirmOverwrite() = 0;
	virtual bool doCreate() = 0;
	virtual void showConclusion() = 0;
};

#endif // DATABASECREATER_H
