#include <QApplication>
#include "maindialog.h"
#include "mysqlcreater.h"

#include <QDebug>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	MainDialog mainDialog;
	mainDialog.show();

	return app.exec();
}

