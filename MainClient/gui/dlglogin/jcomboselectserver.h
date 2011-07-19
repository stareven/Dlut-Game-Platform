#ifndef JCOMBOSELECTSERVER_H
#define JCOMBOSELECTSERVER_H

#include <QComboBox>

#include "shallserver.h"

class JComboSelectServer : public QComboBox
{
Q_OBJECT
public:
    explicit JComboSelectServer(QWidget *parent = 0);
    const SHallServer& getServer()const;
//	void setServerName(const QString&);
private slots:
    void selectedServer(int);
private:
    void readServers();
    void saveServers();
    const QString& getFileName()const;
    void updateServers();
    void addNewServer();
private:
    QList<SHallServer> m_servers;
};

#endif // JCOMBOSELECTSERVER_H
