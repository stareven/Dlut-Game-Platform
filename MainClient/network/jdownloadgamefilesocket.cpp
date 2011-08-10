#include "jdownloadgamefilesocket.h"

#include <QFile>
#include <QCoreApplication>

#include "global/jelapsedtimer.h"

JDownloadGameFileSocket::JDownloadGameFileSocket(QObject *parent) :
    JSocketBase(parent)
{
	m_head.m_isReceived=false;
	m_head.m_nNow=-1;
	m_head.m_nTotal=0;
	m_isError=false;
}

void JDownloadGameFileSocket::rqsGameFile(const QString& gamename,const JVersion& version,const QString& path)
{
	m_path=path;
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<gamename<<version;
	sendData(outdata);
}

bool JDownloadGameFileSocket::waitForConnected( int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(socketState()!=QAbstractSocket::ConnectingState || m_isError)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return socketState()==QAbstractSocket::ConnectedState;
}

bool JDownloadGameFileSocket::waitForDownloaded(int msecs)
{
	JElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<msecs)
	{
		if(m_head.m_nNow==m_head.m_nTotal || m_isError)
		{
			break;
		}
		QCoreApplication::processEvents();
	}
	return m_head.m_nNow==m_head.m_nTotal && m_head.m_nTotal!=0;
}

void JDownloadGameFileSocket::dataProcess(const QByteArray &data)
{
	QDataStream stream(data);
	if(!m_head.m_isReceived)
	{
		stream>>m_head.m_gamename;
		stream>>m_head.m_version;
		stream>>m_head.m_size;
		stream>>m_head.m_pieceSize;
		stream>>m_head.m_nTotal;
		m_head.m_isReceived=true;
		m_head.m_nNow=0;
		if(m_head.m_size>0)
		{
			qDebug()<<"head receive success.";
			m_file=new QFile(m_path,this);
			m_file->open(QIODevice::WriteOnly);
		}
	}else{
		qint64 i;
		QByteArray filedata;
		stream>>i;
		stream>>filedata;
		if(i!=m_head.m_nNow)
		{
			qDebug()<<"JDownloadGameFileSocket::dataProcess:sequence error.";
			qDebug()<<"receive num:"<<i<<"logic:"<<m_head.m_nNow;
			m_isError=true;
			return;
		}
		m_file->write(filedata);
		m_head.m_nNow++;
		if(m_head.m_nNow==m_head.m_nTotal)
		{
			m_file->setPermissions(m_file->permissions() | QFlags<QFile::Permission>(0x1111));
			m_file->close();
		}
	}
}
