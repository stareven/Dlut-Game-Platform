#include <QtGui/QApplication>
#include "gui/mainwindow.h"
#include "gui/dlglogin/jdlglogin.h"
#include "gui/jdlgselectserver.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
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
