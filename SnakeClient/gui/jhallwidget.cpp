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
//	m_socket->setObjectName("socket");
	m_reqUserInfo=new JRequestUserInfo(this);
	m_reqPort=new JRequestPort(this);
	connect(m_socket,SIGNAL(rcvHello(JCode)),SLOT(om_socket_rcvHello(JCode)));
	connect(m_socket,SIGNAL(rcvUserlist(JID,QList<JID>)),SLOT(om_socket_rcvUserlist(JID,QList<JID>)));
	connect(m_socket,SIGNAL(rcvAddRoom(Snake::JRoom)),SLOT(om_socket_rcvAddRoom(Snake::JRoom)));
	connect(m_socket,SIGNAL(rcvEnterRoom(JID,JID)),SLOT(om_socket_rcvEnterRoom(JID,JID)));
	connect(m_socket,
			SIGNAL(rcvEscapeRoom(JID,JID)),
			SLOT(om_socket_rcvEscapeRoom(JID,JID)));
	ui->setupUi(this);
	m_roomlistmodel=new JRoomListModel(this);
	ui->listView_room->setModel(m_roomlistmodel);
	m_reqPort->setServerPort(EST_FREEPORT,SHost(GlobalSettings::g_mainServer.m_address,GlobalSettings::g_mainServer.m_port));
	m_socket->sendHello(JCryproRecorder().getUserId());
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

//void JHallWidget::om_socket_SocketCode(JCode code)
//{
//	switch((ENet)code)
//	{
//	case EN_CONNECTED:
//		{
//			JCryproRecorder cr;
//			m_socket->sendHello(cr.getUserId());
//		}
//		break;
//	case EN_DISCONNECTED:
//		qDebug()<<"socket disconnected";
//		break;
//	}
//}

void JHallWidget::om_socket_rcvHello(JCode code)
{
	if(0==code)
	{
		m_socket->sendRqsUserlist();
	}
}

void JHallWidget::om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	if(roomId!=0) return;
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
	ui->lst_player->clear();
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
	Snake::JRoom room (QInputDialog::getText(this,
										  tr("input room name"),
										  tr("please input the name of the room")));
	if(room.getRoomName().isNull() || room.getRoomName().isEmpty())
	{
		return;
	}
//	room.m_roomId=-1;
	m_socket->sendAddRoom(room);
}

void JHallWidget::om_socket_rcvAddRoom(const Snake::JRoom& room)
{
	qDebug()<<room.getRoomId()<<room.getRoomName();
}

void JHallWidget::om_socket_rcvEnterRoom(JID roomId,JID userId)
{
	if(roomId>0 && userId==JCryproRecorder().getUserId())
	{
		emit enterGame(1);
	}
}

void JHallWidget::om_socket_rcvEscapeRoom(JID roomId,JID userId)
{
	if(0==roomId)
	{
		QList<QListWidgetItem *> items=ui->lst_player->findItems(tr("%1:").arg(userId),Qt::MatchStartsWith);
		foreach(QListWidgetItem* item,items)
		{
			ui->lst_player->removeItemWidget(item);
		}
	}
}

void JHallWidget::on_btn_enter_room_clicked()
{
	JID roomId;
	roomId=m_roomlistmodel->data(ui->listView_room->currentIndex(),Qt::EditRole).toInt();
	m_socket->sendEnterRoom(roomId);
}

void JHallWidget::on_btn_refresh_room_clicked()
{
	m_socket->sendRqsRoomlist();
}
