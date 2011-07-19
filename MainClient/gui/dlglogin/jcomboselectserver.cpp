#include "jcomboselectserver.h"

JComboSelectServer::JComboSelectServer(QWidget *parent) :
    QComboBox(parent)
{
    readServers();
    updateServers();
    connect(this,SIGNAL(activated(int)),this,SLOT(selectedServer(int)));
}

const SHallServer& JComboSelectServer::getServer()const
{
    if(currentIndex()<m_servers.size())
        return m_servers.at(this->currentIndex());
    static SHallServer noserver;
    return noserver;
}

//void JComboSelectServer::setServerName(const QString& name)
//{
//    if(currentIndex()<m_servers.size())
//    {
//        m_servers[(currentIndex())].setName(name);
//        this->updateServers();
//    }
//}

void JComboSelectServer::selectedServer(int index)
{
    if(index==m_servers.count())
    {
        addNewServer();
    }
    //emit selectUpdate();
}

#include "jdlgnewserver.h"

void JComboSelectServer::addNewServer()
{
    JDlgNewServer dlg(this);
    if(dlg.exec()==QDialog::Accepted)
    {
        m_servers.append(dlg.getServer());
        updateServers();
        this->setCurrentIndex(m_servers.count()-1);
    }
}

#include <QSettings>

void JComboSelectServer::readServers()
{
    QSettings settings(getFileName(), QSettings::IniFormat,this);
    QStringList list=settings.childGroups();
    foreach(QString str,list)
    {
		QString address;
        quint16 port;
        address=settings.value(QString("%1/%2").arg(str).arg("address")).toString();
        port=settings.value(QString("%1/%2").arg(str).arg("port")).toInt();
		m_servers.append(SHallServer(QHostAddress(address),port));
    }
	return;
}

void JComboSelectServer::saveServers()
{
    QSettings settings(getFileName(), QSettings::IniFormat,this);
    settings.clear();
    foreach(SHallServer server,m_servers)
	{
		settings.setValue(QString("%1/%2").arg(server.getAddress().toString()).arg("address"),server.getAddress().toString());
		settings.setValue(QString("%1/%2").arg(server.getAddress().toString()).arg("port"),server.getPort());
    }
}

const QString& JComboSelectServer::getFileName()const
{
    static QString fn="servers.ini";
    return fn;
}

void JComboSelectServer::updateServers()
{
	clear();
    foreach(SHallServer server,m_servers)
    {
		addItem(server.toString());
    }
	addItem("new server");
    saveServers();
}
