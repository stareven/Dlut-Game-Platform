#ifndef JDLGNEWSERVER_H
#define JDLGNEWSERVER_H

#include <QDialog>
#include "shallserver.h"

namespace Ui {
    class JDlgNewServer;
}

class JDlgNewServer : public QDialog {
    Q_OBJECT
public:
    JDlgNewServer(QWidget *parent = 0);
    ~JDlgNewServer();

    SHallServer getServer()const;

protected:
    void changeEvent(QEvent *e);
    void accept();
private:
    Ui::JDlgNewServer *ui;
};

#endif // JDLGNEWSERVER_H
