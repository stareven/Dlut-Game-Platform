#include "jdlglogin.h"
#include "ui_jdlglogin.h"

//#include "jdatacenter.h"
//#include "norwegianwoodstyle.h"

#include <QMessageBox>

#include "service/jrequestlogin.h"
//#include "network/jloginsocket.h"
#include "global/elogin.h"
#include "service/jrequestport.h"

#include <QPalette>

JDlgLogin::JDlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDlgLogin)
{
	m_rqslogin=new JRequestLogin(this);
	m_rqslogin->setObjectName("rqsloginsrv");
    ui->setupUi(this);
    ui->edt_username->setText(m_remember.getUserName());
    ui->edt_passwd->setText(m_remember.getPassWord());
    ui->chb_rememberpassword->setChecked(m_remember.getIsRemember());
    ui->chb_autologin->setChecked(m_remember.getIsAutoLogin());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
     palette.setColor(QPalette::WindowText, QColor(Qt::green));
    ui->lab_username->setPalette(palette);
    ui->lab_message->setPalette(palette);
    ui->lab_passwd->setPalette(palette);
    ui->lab_role->setPalette(palette);
    ui->lab_server->setPalette(palette);
    ui->chb_autologin->setPalette(palette);
    ui->chb_rememberpassword->setPalette(palette);
    connect(this,SIGNAL(autoLogin()),this,SLOT(accept()),Qt::QueuedConnection);
    //QApplication::setStyle(new NorwegianWoodStyle);
}

JDlgLogin::~JDlgLogin()
{
    delete ui;
}

void JDlgLogin::changeEvent(QEvent *e)
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

void JDlgLogin::accept()
{
    if(ui->edt_username->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("username is empty"),
                              tr("username can not be empty!")
                              );
        return;
    }
    if(ui->edt_passwd->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("password is empty"),
                              tr("password can not be empty!")
                              );
        return;
    }
    if(ui->cb_server->getServer().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("server is empty"),
                              tr("server can not be empty!")
                              );
        return;
        return;
    }
    m_remember.setIsRemember(ui->chb_rememberpassword->isChecked());
    m_remember.setIsAutoLogin(ui->chb_autologin->isChecked());
    if(ui->chb_rememberpassword->isChecked())
    {
        m_remember.remember();
    }else{
        m_remember.remove();
	}
	JRequestPort ps;
    ps.setServerPort(EST_FREEPORT,SHost(ui->cb_server->getServer().getAddress(),ui->cb_server->getServer().getPort()));
    SHost host=ps.rqsServerPort(EST_LOGIN);
	m_rqslogin->connectToHost(host.m_address,host.m_port);
	ui->lab_message->setText(tr("connecting to server"));
	if(!m_rqslogin->waitForConnected(1000))
	{
		ui->lab_message->setText(tr("connect failed : %1").arg(m_rqslogin->getConnectError()));
		return;
	}
	m_rqslogin->login(ui->edt_username->text(),
					  ui->edt_passwd->text(),
					  ui->cb_role->currentIndex());
	ui->lab_message->setText(tr("begin to login"));
	if(!m_rqslogin->waitForLogined(1000))
	{
		ui->lab_message->setText(tr("login failed : ").arg(m_rqslogin->getLoginError()));
		return;
	}
	done(QDialog::Accepted);
//	m_rqsloginsrv->login(ui->edt_username->text(),
//		      ui->edt_passwd->text(),
//		      ui->cb_role->currentIndex(),
//                      host.m_address,
//                      host.m_port);
//    JLoginService loginsvc(this);
//    JCode code;
//    if((code=loginsvc.login(ui->edt_username->text(),
//		      ui->edt_passwd->text(),
//		      ui->cb_role->currentIndex())))
//    {
//	ui->lab_message->setText(tr("login succeed"));
//	done(1);
//    }else{
//	ui->lab_message->setText(tr("login failed . code :%1").arg(code));
//	return;
//    }
}

void JDlgLogin::error(QAbstractSocket::SocketError e)
{
    qDebug()<<e;
    ui->lab_message->setText(tr("error"));
}

void JDlgLogin::on_edt_username_editingFinished()
{
    m_remember.changeUserName(ui->edt_username->text());
    ui->edt_passwd->setText(m_remember.getPassWord());
}

void JDlgLogin::on_edt_passwd_editingFinished()
{
    m_remember.setPassWord(ui->edt_passwd->text());
}

//void JDlgLogin::on_cb_server_selectUpdate()
//{
//    ui->lab_message->setText(tr("connecting to server %1").arg(ui->cb_server->getServer().toString()));
//}

//void JDlgLogin::on_loginsrv_loginMsg(JCode code)
//{
//    //qDebug()<<"on_loginsrv_loginMsg : "<<code;
////    qDebug()<<loginMsg[code];
//    ui->lab_message->setText(loginMsg[code]);
//    if(code==EL_SUCCESS) done(QDialog::Accepted);
////    switch(code)
////    {
////    case 0:
////	outputLoginMsg("login success");
////	this->done(QDialog::Accepted);
////	break;
////    case 1:
////	outputLoginMsg("no such user");
////	break;
////    case 2:
////	outputLoginMsg("password wrong");
////	break;
////    case 3:
////	outputLoginMsg("no such role");
////	break;
////    case LC_CONNECTED:
////	outputLoginMsg("connected");
////	break;
////    case LC_UNWRITABLE:
////	outputLoginMsg("socket can not write");
////	break;
////    case LC_DISCONNECTED:
////	outputLoginMsg("socket disconnected");
////	break;
////    case JLoginService::LM_BEGIN_TO_LOGIN:
////	outputLoginMsg("begin to login");
////	break;
////	case 0x40:
////	outputLoginMsg("has already logined.");
////	break;
////    }
//}

//void JDlgLogin::outputLoginMsg(const char* msg)
//{
//    QString strmsg=tr(msg);
//    qDebug()<<strmsg;
//    ui->lab_message->setText(strmsg);
//}
