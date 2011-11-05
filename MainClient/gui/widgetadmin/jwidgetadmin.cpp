#include "jwidgetadmin.h"
#include "ui_jwidgetadmin.h"

#include <ClientRequest/JCommandSendBase>

#include <QDebug>

JWidgetAdmin::JWidgetAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JWidgetAdmin)
{
    ui->setupUi(this);
}

JWidgetAdmin::~JWidgetAdmin()
{
    delete ui;
}

void JWidgetAdmin::on_btn_shutdown_mainserver_clicked()
{
	qDebug()<<"JWidgetAdmin::on_btn_shutdown_mainserver_clicked";
	JCommandSendBase csb;
	csb.sendShutdown();
}

void JWidgetAdmin::on_btn_restart_mainserver_clicked()
{
	qDebug()<<"JWidgetAdmin::on_btn_restart_mainserver_clicked";
	JCommandSendBase csb;
	csb.sendRestart();;
}
