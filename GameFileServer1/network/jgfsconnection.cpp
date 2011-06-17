#include "jgfsconnection.h"

#include <QDataStream>
#include <QFile>
#include <QDebug>

#include "global/jversion.h"
#include "service/jgamefilemanager.h"

JGfsConnection::JGfsConnection(QTcpSocket* socket,QObject *parent) :
	JConnectionBase(socket,parent)
{
}

void JGfsConnection::dataProcess(const QByteArray& data)
{
	QDataStream stream(data);
	QString gamename;
	JVersion version;
	qint64 size;
	stream>>gamename>>version;
	JGameFileManager gfm;
	QString filepath=gfm.getFilePath(gamename,version);
	QFile file(filepath,this);
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug()<<"file open error:"<<filepath<<file.errorString();
		size=0;
	}else{
		size=file.size();
	}
	const qint64 SIZE_PIECE=8*1024;
	qint64 n=size/SIZE_PIECE;
	{
		QByteArray outdata;
		QDataStream outstream(&outdata,QIODevice::WriteOnly);
		outstream<<gamename<<version<<size;
		outstream<<SIZE_PIECE<<n;
		sendData(outdata);
	}
	for(qint64 i=0;i<n;++i)
	{
		QByteArray outdata;
		QDataStream outstream(&outdata,QIODevice::WriteOnly);
		outstream<<i;
		outstream<<file.read(SIZE_PIECE);
		sendData(outdata);
	}
}
