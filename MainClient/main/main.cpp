#include <QtGui/QApplication>
#include "gui/mainwindow.h"
#include "gui/dlglogin/jdlglogin.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	JDlgLogin dlg;
	if(dlg.exec()==QDialog::Rejected)
    {
        return 0;
	}
    MainWindow w;
    w.show();
    return a.exec();
}
