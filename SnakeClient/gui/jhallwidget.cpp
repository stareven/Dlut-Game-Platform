#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include "network/jsnakesocket.h"
#include "service/jglobalsettings.h"
#include "service/jrequestuserinfo.h"
#include "service/jrequestport.h"
#include "service/jcryprorecorder.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
	m_socket=new JSnakeSocket(this);
	m_socket->setObjectName("socket");
	m_reqUserInfo=new JRequestUserInfo(this);
	m_reqPort=new JRequestPort(this);
    ui->setupUi(this);
	m_reqPort->setServerPort(EST_FREEPORT,SHost(GlobalSettings::g_mainServer.m_address,GlobalSettings::g_mainServer.m_port));
	m_socket->connectToHost(GlobalSettings::g_gameServer.m_address,GlobalSettings::g_gameServer.m_port);

}

JHallWidget::~JHallWidget()
{
    delete ui;
}

void JHallWidget::on_btn_refresh_clicked()
{
	ui->lst_player->clear();
	m_socket->sendRqsUserlist();
}

void JHallWidget::on_socket_SocketCode(JCode code)
{
	switch((ENet)code)
	{
	case EN_CONNECTED:
		{
			JCryproRecorder cr;
			m_socket->sendHello(cr.getUserId());
		}
		break;
	case EN_DISCONNECTED:
		qDebug()<<"socket disconnected";
		break;
	}
}

void JHallWidget::on_socket_rcvHello(JCode code)
{
	qDebug()<<"JHallWidget::on_socket_rcvHello:"<<code;
	if(0==code)
	{
		m_socket->sendRqsUserlist();
	}
}

void JHallWidget::on_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	qDebug()<<"JHallWidget::on_socket_rcvUserlist:"<<roomId;
	SHost hostuserinfo=m_reqPort->rqsServerPort(EST_USERINFO);
	m_reqUserInfo->connectToHost(hostuserinfo.m_address,hostuserinfo.m_port);
	qDebug()<<"user info begin to connect";
	if(!m_reqUserInfo->waitForConnected(1000))
	{
		qDebug()<<"user info connect failed.";
		return;
	}else{
		qDebug()<<"user info connect success.";
	}
	JCryproRecorder cr;
	m_reqUserInfo->sendCrypro(cr.getUserId(),cr.getCrypro());
	if(!m_reqUserInfo->waitForPlh(1000))
	{
		qDebug()<<"user info plh failed.";
		return;
	}else{
		qDebug()<<"user info plh success.";
	}
	foreach(JID userId,userlist)
	{
		UserInfo::SUserInfo userinfo=m_reqUserInfo->rqsUserInfo(userId);
		if(userinfo.m_userId==userId)
		{
			ui->lst_player->addItem(tr("%1:%2:%3")
									.arg(userinfo.m_userId)
									.arg(userinfo.m_nickname)
									.arg(userinfo.m_organization));
		}else{
			ui->lst_player->addItem(tr("%1").arg(userId));
		}
	}
}
