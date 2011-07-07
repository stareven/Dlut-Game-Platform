#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include "network/jsnakesocket.h"
#include "service/jglobalsettings.h"
#include "service/jrequestuserinfo.h"
#include "service/jrequestport.h"
#include "service/jcryprorecorder.h"
#include "service/jroomlistmodel.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
	m_socket=&JSnakeSocket::getInstance();
//	m_socket->setParent(this);
	m_socket->setObjectName("socket");
	m_reqUserInfo=new JRequestUserInfo(this);
	m_reqPort=new JRequestPort(this);
	connect(m_socket,SIGNAL(SocketCode(JCode)),SLOT(on_socket_SocketCode(JCode)));
	connect(m_socket,SIGNAL(rcvHello(JCode)),SLOT(on_socket_rcvHello(JCode)));
	connect(m_socket,SIGNAL(rcvUserlist(JID,QList<JID>)),SLOT(on_socket_rcvUserlist(JID,QList<JID>)));
	connect(m_socket,SIGNAL(rcvAddRoom(Snake::JRoom)),SLOT(on_socket_rcvAddRoom(Snake::JRoom)));
	ui->setupUi(this);
	m_roomlistmodel=new JRoomListModel(this);
	ui->listView_room->setModel(m_roomlistmodel);
	m_reqPort->setServerPort(EST_FREEPORT,SHost(GlobalSettings::g_mainServer.m_address,GlobalSettings::g_mainServer.m_port));
	m_socket->connectToHost(GlobalSettings::g_gameServer.m_address,GlobalSettings::g_gameServer.m_port);
}

JHallWidget::~JHallWidget()
{
	delete ui;
}

void JHallWidget::on_btn_refresh_userlist_clicked()
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

#include <QInputDialog>

#include "jsnakeglobal.h"

void JHallWidget::on_btn_create_room_clicked()
{
	Snake::JRoom room;
	room.m_roomName=QInputDialog::getText(this,
										  tr("input room name"),
										  tr("please input the name of the room"));
	if(room.m_roomName.isNull() || room.m_roomName.isEmpty())
	{
		return;
	}
	room.m_roomId=-1;
	m_socket->sendAddRoom(room);
}

void JHallWidget::on_socket_rcvAddRoom(const Snake::JRoom& room)
{
	qDebug()<<room.m_roomId<<room.m_roomName;
}
