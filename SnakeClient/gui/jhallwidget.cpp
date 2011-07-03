#include "jhallwidget.h"
#include "ui_jhallwidget.h"

#include "network/jsnakesocket.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
	m_socket=new JSnakeSocket(this);
	m_socket->setObjectName("socket");
    ui->setupUi(this);
	m_socket->sendHello(250);
}

JHallWidget::~JHallWidget()
{
    delete ui;
}

void JHallWidget::on_btn_refresh_clicked()
{
	m_socket->sendRqsUserlist();
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
