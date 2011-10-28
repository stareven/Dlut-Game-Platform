#include <QtCore/QCoreApplication>
#include <QDebug>

#include "network/jmainserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JMainServer mainserver;
    qDebug()<<"main server run : port is "<<mainserver.run(37373);
    return a.exec();
}
