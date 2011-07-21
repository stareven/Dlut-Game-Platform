#include "jcomboselectserver.h"

#include <QSettings>

#include "jdlgnewserver.h"

JComboSelectServer::JComboSelectServer(QWidget *parent) :
    QComboBox(parent)
{
    readServers();
    updateServers();
	connect(this,SIGNAL(activated(int)),SLOT(selectedServer(int)));
}

const SHallServer& JComboSelectServer::getServer()const
{
    if(currentIndex()<m_servers.size())
        return m_servers.at(this->currentIndex());
    static SHallServer noserver;
    return noserver;
}

void JComboSelectServer::selectedServer(int index)
{
    if(index==m_servers.count())
    {
        addNewServer();
	}else{
		QSettings settings(getFileName(), QSettings::IniFormat,this);
		settings.setValue(tr("select/current"),index);
	}
}

void JComboSelectServer::addNewServer()
{
    JDlgNewServer dlg(this);
    if(dlg.exec()==QDialog::Accepted)
    {
        m_servers.append(dlg.getServer());
        updateServers();
		saveServers();
		setCurrentIndex(m_servers.count()-1);
    }
}

void JComboSelectServer::readServers()
{
    QSettings settings(getFileName(), QSettings::IniFormat,this);
	int size = settings.beginReadArray("servers");
	for(int i=0;i<size;++i)
	{
		settings.setArrayIndex(i);
		QString address;
		quint16 port;
		address=settings.value("address").toString();
		port=settings.value("port").toInt();
		if(QHostAddress(address).isNull()) continue;
		m_servers.append(SHallServer(QHostAddress(address),port));
	}
	settings.endArray();
}

void JComboSelectServer::saveServers()
{
    QSettings settings(getFileName(), QSettings::IniFormat,this);
	settings.beginWriteArray("servers");
	for(int i=0;i<m_servers.size();++i)
	{
		settings.setArrayIndex(i);
		settings.setValue("address",m_servers[i].getAddress().toString());
		settings.setValue("port",m_servers[i].getPort());
	}
	settings.endArray();
}

const QString& JComboSelectServer::getFileName()const
{
    static QString fn="servers.ini";
    return fn;
}

void JComboSelectServer::updateServers()
{
	clear();
	QSettings settings(getFileName(), QSettings::IniFormat,this);
	int select=settings.value(tr("select/current"),0).toInt();
    foreach(SHallServer server,m_servers)
    {
		addItem(server.toString());
    }
	addItem("new server");
	setCurrentIndex(select);
}
