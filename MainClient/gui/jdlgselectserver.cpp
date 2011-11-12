#include "jdlgselectserver.h"
#include "ui_jdlgselectserver.h"
#include "dlglogin/jdlgnewserver.h"

#include <DataStruct/JServerInfo>
#include <ClientRequest/JRequestBase>

#include <QPalette>
#include <QMessageBox>

JDlgSelectServer::JDlgSelectServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgSelectServer)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
     palette.setColor(QPalette::WindowText, QColor(Qt::green));
     ui->lab_text->setPalette(palette);
}

JDlgSelectServer::~JDlgSelectServer()
{
    delete ui;
}

void JDlgSelectServer::accept()
{
	if(ui->cb_servers->getServer().isEmpty())
	{
		QMessageBox::critical(this,
							  tr("server is empty"),
							  tr("server can not be empty!")
							  );
		return;
	}
	JRequestBase req;
	const SHallServer& server = ui->cb_servers->getServer();
	ui->label_info->setText(
			tr("connection to server %1:%2")
			.arg(server.getAddress().toString())
			.arg(server.getPort())
			);
	req.connectToHost(server.getAddress(),server.getPort());
	if(req.waitForConnected(1000)){
		ui->label_info->setText(
				tr("connect succeed")
				);
		QDialog::accept();
	}else{
		ui->label_info->setText(
				tr("connect failed : %1")
				.arg(req.getConnectError())
				);
	}
}

void JDlgSelectServer::on_btn_add_clicked()
{
	JDlgNewServer dlg(this);
	if(dlg.exec()==QDialog::Accepted)
	{
		ui->cb_servers->addServer(dlg.getServer());
	}

}

void JDlgSelectServer::on_btn_remove_clicked()
{
	ui->cb_servers->removeCurrentServer();
}
