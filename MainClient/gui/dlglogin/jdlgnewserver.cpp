#include "jdlgnewserver.h"
#include "ui_jdlgnewserver.h"

#include <QPalette>

JDlgNewServer::JDlgNewServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgNewServer)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
    palette.setColor(QPalette::Base, QColor(0,0,0));
     palette.setColor(QPalette::WindowText, QColor(Qt::green));
     palette.setColor(QPalette::Text, QColor(Qt::red));
     ui->edt_address->setPalette(palette);
     ui->edt_port->setPalette(palette);
     ui->lab_address->setPalette(palette);
     ui->lab_port->setPalette(palette);
}

JDlgNewServer::~JDlgNewServer()
{
    delete ui;
}

void JDlgNewServer::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

#include <QMessageBox>

void JDlgNewServer::accept()
{
    if(QHostAddress(ui->edt_address->text()).isNull())
    {
		QMessageBox::critical(this,
							  tr("address is illegal"),
							  tr("the address you input is illegal!"));
        return;
    }
    bool ok;
    int port;
    port=ui->edt_port->text().toInt(&ok);
    if(!ok || port <0 || port >65535 )
    {
		QMessageBox::critical(this,
							 tr("port is illegal"),
							 tr("the port you input is illegal!"));
        return;
    }
    QDialog::accept();
}

SHallServer JDlgNewServer::getServer()const
{
	return SHallServer(QHostAddress(ui->edt_address->text()),ui->edt_port->text().toInt());
}
