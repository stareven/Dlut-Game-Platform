#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include "network/jsnakesocket.h"
#include "service/jglobalsettings.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
	m_socket=new JSnakeSocket(this);
	m_socket->setObjectName("socket");
    ui->setupUi(this);
	m_socket->connectToHost(GlobalSettings::g_gameServer.m_address,GlobalSettings::g_gameServer.m_port);
}

JHallWidget::~JHallWidget()
{
    delete ui;
}

void JHallWidget::on_btn_refresh_clicked()
{
	m_socket->sendRqsUserlist();
}

void JHallWidget::on_socket_SocketCode(JCode code)
{
	switch((ENet)code)
	{
	case EN_CONNECTED:
		m_socket->sendHello(GlobalSettings::g_userId);
		break;
	case EN_DISCONNECTED:
		qDebug()<<"socket disconnected";
		break;
	}
}

void JHallWidget::on_socket_rcvHello(JCode code)
{
	qDebug()<<"JHallWidget::on_socket_rcvHello:"<<code;
}

void JHallWidget::on_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	qDebug()<<"JHallWidget::on_socket_rcvUserlist:"<<roomId;
	foreach(JID userId,userlist)
	{
		ui->lst_player->addItem(QString::number(userId));
	}
}
