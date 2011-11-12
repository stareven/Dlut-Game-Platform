#ifndef JDLGSELECTSERVER_H
#define JDLGSELECTSERVER_H

#include <QDialog>

#include <Global/Global>

class JServerInfo;

namespace Ui {
    class JDlgSelectServer;
}

class JDlgSelectServer : public QDialog
{
    Q_OBJECT

public:
    explicit JDlgSelectServer(QWidget *parent = 0);
	~JDlgSelectServer();
	void accept();
private:
    Ui::JDlgSelectServer *ui;

private slots:
	void on_btn_remove_clicked();
	void on_btn_add_clicked();
};

#endif // JDLGSELECTSERVER_H
