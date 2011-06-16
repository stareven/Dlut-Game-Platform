#include "jgfsconnection.h"

JGfsConnection::JGfsConnection(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
}
