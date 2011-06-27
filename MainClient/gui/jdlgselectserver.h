#ifndef JDLGSELECTSERVER_H
#define JDLGSELECTSERVER_H

#include <QDialog>

#include "global/jglobal.h"

namespace SubServer
{
	class SSubServer;
}

namespace Ui {
    class JDlgSelectServer;
}

class JDlgSelectServer : public QDialog
{
    Q_OBJECT

public:
    explicit JDlgSelectServer(QWidget *parent = 0);
    ~JDlgSelectServer();
	void addServer(const SubServer::SSubServer&);
	void setText(const QString&);
	JID getSelectedServer()const;
private:
    Ui::JDlgSelectServer *ui;
};

#endif // JDLGSELECTSERVER_H
