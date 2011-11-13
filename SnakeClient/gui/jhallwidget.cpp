#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include <QInputDialog>

#include <ClientRequest/JRequestUserInfo>

#include "jsnakeglobal.h"
#include "network/jsnakeprocessor.h"
#include "service/jglobalsettings.h"
#include "service/jroomlistmodel.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
	m_processor=JSnakeProcessor::getInstance();
	m_reqUserInfo=new JRequestUserInfo(this);
	connect(m_processor,
			SIGNAL(rcvHello(JCode)),
			SLOT(om_socket_rcvHello(JCode)));
	connect(m_processor,
			SIGNAL(rcvUserlist(JID,QList<JID>)),
			SLOT(om_socket_rcvUserlist(JID,QList<JID>)));
	connect(m_processor,
			SIGNAL(rcvAddRoom(Snake::JRoom)),
			SLOT(om_socket_rcvAddRoom(Snake::JRoom)));
	connect(m_processor,
			SIGNAL(rcvEnterRoom(JID,JID)),
			SLOT(om_socket_rcvEnterRoom(JID,JID)));
	connect(m_processor,
			SIGNAL(rcvEscapeRoom(JID,JID)),
			SLOT(om_socket_rcvEscapeRoom(JID,JID)));
	m_roomlistmodel=new JRoomListModel(this);
	ui->setupUi(this);
	ui->listView_room->setModel(m_roomlistmodel);
	m_processor->sendHello(GlobalSettings::g_userId);
	m_processor->sendRqsRoomlist();
}

JHallWidget::~JHallWidget()
{
	delete ui;
}

void JHallWidget::on_btn_refresh_userlist_clicked()
{
	ui->lst_player->clear();
	m_processor->sendRqsUserlist();
}

void JHallWidget::om_socket_rcvHello(JCode code)
{
	if(0==code)
	{
		m_processor->sendRqsUserlist();
	}
}

void JHallWidget::om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	if(roomId!=0) return;
	ui->lst_player->clear();
	foreach(JID userId,userlist)
	{
		qDebug()<<"JHallWidget::om_socket_rcvUserlist:"<<userId;
		addUserToList(userId);
	}
}

void JHallWidget::on_btn_create_room_clicked()
{
	Snake::JRoom room (QInputDialog::getText(this,
										  tr("input room name"),
										  tr("please input the name of the room")));
	if(room.getRoomName().isNull() || room.getRoomName().isEmpty())
	{
		return;
	}
	m_processor->sendAddRoom(room);
}

void JHallWidget::om_socket_rcvAddRoom(const Snake::JRoom& room)
{
	qDebug()<<room.getRoomId()<<room.getRoomName();
}

void JHallWidget::om_socket_rcvEnterRoom(JID roomId,JID userId)
{
	if(roomId>0 && userId==GlobalSettings::g_userId)
	{
		emit enterGame(1);
	}else if(0==roomId){
		addUserToList(userId);
	}
}

void JHallWidget::om_socket_rcvEscapeRoom(JID roomId,JID userId)
{
	qDebug()<<"JHallWidget::om_socket_rcvEscapeRoom:"<<roomId<<userId;
	if(0==roomId)
	{
		QList<QListWidgetItem *> items=ui->lst_player->findItems(tr("%1:").arg(userId),Qt::MatchStartsWith);
		foreach(QListWidgetItem* item,items)
		{
			qDebug()<<"JHallWidget::om_socket_rcvEscapeRoom"<<item->text();
			ui->lst_player->removeItemWidget(item);
			delete item;
		}
	}
}

void JHallWidget::on_btn_enter_room_clicked()
{
	JID roomId;
	roomId=m_roomlistmodel->data(ui->listView_room->currentIndex(),Qt::EditRole).toInt();
	m_processor->sendEnterRoom(roomId);
}

void JHallWidget::on_btn_refresh_room_clicked()
{
	m_processor->sendRqsRoomlist();
}

void JHallWidget::addUserToList(JID userId)
{
	if(ui->lst_player->findItems(tr("%1:").arg(userId),Qt::MatchStartsWith).isEmpty())
	{
		JUserInfo userinfo=m_reqUserInfo->pullUserInfo(userId,1000);
		if(userinfo.getUserId()==userId)
		{
			ui->lst_player->addItem(tr("%1:%2:%3")
									.arg(userinfo.getUserId())
									.arg(userinfo.getNickname())
									.arg(userinfo.getOrganization()));
		}else{
			ui->lst_player->addItem(tr("%1:").arg(userId));
		}
	}
}
