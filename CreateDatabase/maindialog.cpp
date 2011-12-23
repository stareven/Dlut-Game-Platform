#include "maindialog.h"
#include "mysqlcreater.h"
#include "sqlitecreater.h"

#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
	mysqlCreater = new MySQLCreater(this);
	sqliteCreater = new SQLiteCreater(this);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(createDbTypeGroup());
	mainLayout->addStretch();
	mainLayout->addWidget(mysqlCreater);
	mainLayout->addWidget(sqliteCreater);
	sqliteCreater->hide();

	setLayout(mainLayout);
	//	resize(sizeHint());
	setFixedSize(sizeHint());
	setWindowTitle(tr("Create Database"));
}

QGroupBox* MainDialog::createDbTypeGroup() {
	static QGroupBox *dbTypeGroup;
	if (!dbTypeGroup) {
		qDebug() << "createDbTypeGroup called";
		dbTypeGroup = new QGroupBox(tr("Database Type"), this);
		mysqlBtn = new QRadioButton(tr("&MySQL"), this);
		connect(mysqlBtn, SIGNAL(toggled(bool)), mysqlCreater, SLOT(setVisible(bool)));
//		connect(mysqlBtn, SIGNAL(toggled(bool)), this, SLOT(resizeSlot()));
		sqliteBtn = new QRadioButton(tr("SQ&Lite"), this);
		connect(sqliteBtn, SIGNAL(toggled(bool)), sqliteCreater, SLOT(setVisible(bool)));
//		connect(sqliteBtn, SIGNAL(toggled(bool)), this, SLOT(resizeSlot()));
		mysqlBtn->setChecked(true);

		QVBoxLayout *dbTypeLayout = new QVBoxLayout;
		dbTypeLayout->addWidget(mysqlBtn);
		dbTypeLayout->addWidget(sqliteBtn);
		dbTypeLayout->addStretch();
		dbTypeGroup->setLayout(dbTypeLayout);
	}
	return dbTypeGroup;
}

//void MainDialog::resizeSlot() {
//	resize(sizeHint());
//}
