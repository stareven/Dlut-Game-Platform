#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

class QGroupBox;
class QRadioButton;
class QLabel;
class QLineEdit;
class QPushButton;
class DatabaseCreater;

class MainDialog : public QDialog
{
	Q_OBJECT
public:
	explicit MainDialog(QWidget *parent = 0);

private slots:
	//interface
	void convertToMySQLInterface();
	void convertToSQLiteInterface();

	//checker
	void checkDbName(QString name);
	void checkUserName(QString name);
	void checkUserPwd(QString passwd);
	void checkConfirmPwd(QString passwd);

	void reset();

	void create();

private:
	//for check only
	DatabaseCreater* checker;

	//db type
	QGroupBox *dbTypeGroup;
	QRadioButton *mysqlBtn;
	QRadioButton *sqliteBtn;

	//edit
	QLabel *dbNameLabel;
	QLineEdit *dbNameEdit;
	QLabel *dbNameStatus;
	QLabel *userNameLabel;
	QLineEdit *userNameEdit;
	QLabel *userNameStatus;
	QLabel *userPwdLabel;
	QLineEdit *userPwdEdit;
	QLabel *userPwdStatus;
	QLabel *confirmPwdLabel;
	QLineEdit *confirmPwdEdit;
	QLabel *confirmPwdStatus;

	//btn
	QPushButton *createBtn;
	QPushButton *resetBtn;

};

#endif // MAINDIALOG_H
