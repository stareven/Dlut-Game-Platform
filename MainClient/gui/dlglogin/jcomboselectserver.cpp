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

void JComboSelectServer::setServerName(const QString& name)
{
    //qDebug()<<name;
    if(currentIndex()<m_servers.size())
    {
        m_servers[(currentIndex())].setName(name);
        this->updateServers();
    }
}

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
        QString name,address;
        quint16 port;
        name=settings.value(QString("%1/%2").arg(str).arg("name")).toString();
        address=settings.value(QString("%1/%2").arg(str).arg("address")).toString();
        port=settings.value(QString("%1/%2").arg(str).arg("port")).toInt();
        m_servers.append(SHallServer(name,QHostAddress(address),port));
    }
    return;
    m_servers.append(SHallServer("unknown",QHostAddress("127.0.0.1"),37373));
    m_servers.append(SHallServer("unknown",QHostAddress("127.0.0.1"),37374));
}

void JComboSelectServer::saveServers()
{
    QSettings settings(getFileName(), QSettings::IniFormat,this);
    settings.clear();
    foreach(SHallServer server,m_servers)
    {
        settings.setValue(QString("%1/%2").arg(server.getName()).arg("name"),server.getName());
        settings.setValue(QString("%1/%2").arg(server.getName()).arg("address"),server.getAddress().toString());
        settings.setValue(QString("%1/%2").arg(server.getName()).arg("port"),server.getPort());
    }
}

const QString& JComboSelectServer::getFileName()const
{
    static QString fn="servers.ini";
    return fn;
}

void JComboSelectServer::updateServers()
{
    this->clear();
    foreach(SHallServer server,m_servers)
    {
        this->addItem(server.toString());
    }
    this->addItem("new server");
    saveServers();
}
