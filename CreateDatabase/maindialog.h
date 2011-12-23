#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

class QSettings;
class DatabaseCreater;
class QGroupBox;
class QRadioButton;
//class QLayout;

class MainDialog : public QDialog
{
	Q_OBJECT
public:
	explicit MainDialog(QWidget *parent = 0);

private slots:
//	void resizeSlot();

private:
	DatabaseCreater *mysqlCreater;
	DatabaseCreater *sqliteCreater;
	QRadioButton *mysqlBtn;
	QRadioButton *sqliteBtn;
//	QLayout *mainLayout;

	QGroupBox* createDbTypeGroup();
};

#endif // MAINDIALOG_H
