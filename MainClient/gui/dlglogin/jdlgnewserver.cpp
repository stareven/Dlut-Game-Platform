#include "jdlgnewserver.h"
#include "ui_jdlgnewserver.h"

JDlgNewServer::JDlgNewServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgNewServer)
{
    ui->setupUi(this);
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
        QMessageBox(QMessageBox::Warning,tr("error"),tr("the address is illegal!"),QMessageBox::Ok,this).exec();
        return;
    }
    bool ok;
    int port;
    port=ui->edt_port->text().toInt(&ok);
    if(!ok || port <0 || port >65535 )
    {
        QMessageBox(QMessageBox::Warning,tr("error"),tr("the port is illegal!"),QMessageBox::Ok,this).exec();
        return;
    }
    if(ui->edt_name->text().isEmpty())
    {
        QMessageBox(QMessageBox::Warning,tr("error"),tr("the name is illegal!"),QMessageBox::Ok,this).exec();
        return;
    }
    QDialog::accept();
}

SHallServer JDlgNewServer::getServer()const
{
    return SHallServer(ui->edt_name->text(),QHostAddress(ui->edt_address->text()),ui->edt_port->text().toInt());
}
