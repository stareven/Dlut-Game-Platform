#include "jwidgetadmin.h"
#include "ui_jwidgetadmin.h"

#include <Global/Command>
#include <Global/CodeError>

#include <ClientRequest/JCommandSendBase>
#include <ClientRequest/JRequestUserRegister>

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

void JWidgetAdmin::on_buttonBox_accepted()
{
	QString loginname = ui->edt_loginname->text();
	QString password = ui->edt_password->text();
	JID iRole = ui->cb_role->currentIndex();
	ui->lab_msg->setText(
				tr("loginname:%1 password:%2 role:%3")
				.arg(loginname)
				.arg(password)
				.arg(iRole)
				);
	if(iRole <0 || iRole > ROLE_ROOT){
		ui->lab_msg->setText(tr("role overflow"));
		return;
	}
	ERole role=(ERole)iRole;
	JRequestUserRegister rur;
	rur.sendRegister(loginname,password,role);
	if(rur.waitForRegisterResult(1000)){
		ui->lab_msg->setText(tr("add user success"));
	}else{
		ui->lab_msg->setText(tr("add user failed:%1").arg(rur.getRegisterError()));
	}
}
