#include "jdialogupdateuserinfo.h"
#include "ui_jdialogupdateuserinfo.h"

#include <Global/CodeError>
#include <DataStruct/JUserInfo>
#include <Socket/JMainClientSocket>
#include <Session/JSession>
#include <ClientRequest/JUploadUserInfo>

#include <QMessageBox>

JDialogUpdateUserInfo::JDialogUpdateUserInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDialogUpdateUserInfo)
{
	m_upload = new JUploadUserInfo(this);
    ui->setupUi(this);
}

JDialogUpdateUserInfo::~JDialogUpdateUserInfo()
{
    delete ui;
}

void JDialogUpdateUserInfo::setInitUserInfo(const JUserInfo& userinfo)
{
	ui->lineEdit_nickname->setText(userinfo.getNickname());
	ui->lineEdit_organization->setText(userinfo.getOrganization());
}

void JDialogUpdateUserInfo::accept()
{
	JID myuserid = JMainClientSocket::getInstance()->getSession()->getUserId();
	QString mynickname = ui->lineEdit_nickname->text();
	QString myorganization = ui->lineEdit_organization->text();
	JUserInfo myuserinfo(myuserid,mynickname,myorganization);
	if(ESuccess == m_upload->pushUserInfo(myuserinfo,1000)){
		QMessageBox::information(this,
								 tr("update user info success"),
								 tr("update user info success")
								 );
		QDialog::accept();
	}else{
		QMessageBox::critical(this,
							  tr("update user info failed"),
							  tr("update user info failed , error :%1").arg(m_upload->getSendResult(myuserid))
							  );
	}
}
