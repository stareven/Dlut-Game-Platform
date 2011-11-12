#include <QtGui/QApplication>
#include "gui/mainwindow.h"
#include "gui/dlglogin/jdlglogin.h"
#include "gui/jdlgselectserver.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	JDlgSelectServer dlgs;
	if(dlgs.exec() ==QDialog::Rejected){
		return 0;
	}
	JDlgLogin dlg;
	if(dlg.exec()==QDialog::Rejected)
    {
        return 0;
	}
    MainWindow w;
    w.show();
    return a.exec();
}
