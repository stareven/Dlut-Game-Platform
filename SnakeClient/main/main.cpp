#include <QtGui/QApplication>
#include "gui/mainwindow.h"

#include "service/jglobalsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
