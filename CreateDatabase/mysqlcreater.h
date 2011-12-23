#ifndef MYSQLCREATER_H
#define MYSQLCREATER_H

#include "databasecreater.h"
class QLabel;
class QLineEdit;
class QPushButton;
class QLayout;

class MySQLCreater : public DatabaseCreater
{
    Q_OBJECT
public:
	explicit MySQLCreater(QWidget *parent = 0);
	~MySQLCreater();

private slots:
	virtual void reset();
	virtual void create();
	void checkUserName(QString name);
	void checkUserPwd(QString passwd);
	void checkConfirmPwd(QString passwd);

private:
	QLabel *userNameLabel;
	QLineEdit *userNameEdit;
	QLabel *userNameStatus;
	QLabel *userPwdLabel;
	QLineEdit *userPwdEdit;
	QLabel *userPwdStatus;
	QLabel *confirmPwdLabel;
	QLineEdit *confirmPwdEdit;
	QLabel *confirmPwdStatus;

	bool doCheckPwdLength(QString passwd);
	bool doCheckConfirmPwd(QString passwd);
	virtual bool finalCheck();
	bool finalCheckDbName();
	bool finalCheckUserName();
	bool finalCheckPwd();
	bool tryRootPwd();
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

#endif // MYSQLCREATER_H
