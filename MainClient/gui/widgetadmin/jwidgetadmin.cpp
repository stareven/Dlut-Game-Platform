#include "jwidgetadmin.h"
#include "ui_jwidgetadmin.h"

#include <Global/Command>
#include <Global/CodeError>

#include <ClientRequest/JCommandSendBase>

JWidgetAdmin::JWidgetAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JWidgetAdmin)
{
	m_send=new JCommandSendBase(this);
	m_send->setObjectName("send");
    ui->setupUi(this);
}

JWidgetAdmin::~JWidgetAdmin()
{
    delete ui;
}

void JWidgetAdmin::on_btn_shutdown_mainserver_clicked()
{
	JCommandSendBase csb;
	csb.sendShutdown();
}

void JWidgetAdmin::on_btn_restart_mainserver_clicked()
{
	JCommandSendBase csb;
	csb.sendRestart();;
}

void JWidgetAdmin::on_send_receiveCommandResult(JID type,JCode result)
{
	QString action;
	QString error;
	switch(type){
	case ECT_Shutdown:
		action=tr("shut down");
		break;
	case ECT_Restart:
		action=tr("restart");
		break;
	default:
		action=tr("unknow action");
		break;
	}
	switch(result){
	case EPermissionDenied:
		error = tr("permission denied");
		break;
	default:
		error = tr("unknow error:%1").arg(result);
		break;
	}
	if(ESuccess == result){
		ui->label->setText(tr("%1 operation success").arg(action));
	}else{
		ui->label->setText(tr("%1 operation error:%2").arg(action).arg(error));
	}
}
