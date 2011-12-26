#include <QtGui/QApplication>
#include <QFile>

#include "gui/gamehall/mainwindow.h"
#include "gui/login/jdlglogin.h"
#include "gui/selectserver/jdlgselectserver.h"

void loadStyles(){
	QFile qss("styles/mc.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	loadStyles();
	if(JDlgSelectServer().exec() ==QDialog::Rejected){
		return 0;
	}
	if(JDlgLogin().exec()==QDialog::Rejected)
    {
        return 0;
	}
    MainWindow w;
    w.show();
    return a.exec();
}
