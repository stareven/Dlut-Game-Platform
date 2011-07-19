#include "jsnakewidget.h"
#include "ui_jsnakewidget.h"

#include "jsnakegame.h"

#include <QPainter>
//#include <QTime>
#include <QTimer>
#include <QKeyEvent>
//#include <QDebug>
#include <QPixmap>
#include <QtGui/QGridLayout>
#include <QLabel>
#include <QLCDNumber>

#include "network/jsnakesocket.h"
#include "service/jcryprorecorder.h"

const int INITX=20;
const int INITY=30;
const int SQUARE_SIZE=18;

JSnakeWidget::JSnakeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JSnakeWidget)
{
	m_game=new JSnakeGame;
    ui->setupUi(this);
	m_roomId=-1;
	m_command=JSnake::ED_NONE;
//    QWidget *gridLayoutWidget;
//    QGridLayout *gridLayout;
//    gridLayoutWidget = new QWidget(this);
//    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
//    gridLayoutWidget->setGeometry(QRect(MAXX*SQUARE_SIZE+INITX+10, 70, 200, 135));
//    gridLayout = new QGridLayout(gridLayoutWidget);
//    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
//    gridLayout->setContentsMargins(0, 0, 0, 0);
	ui->gridLayout->addWidget(new QLabel(tr("ready"),this),0,1,1,1);
	ui->gridLayout->addWidget(new QLabel(tr("life"),this),0,2,1,1);
	ui->gridLayout->addWidget(new QLabel(tr("score"),this),0,3,1,1);
    for(int i=0;i<NUM_SNAKE;++i)
    {
		ui->gridLayout->addWidget(new QLabel(tr("snake%1")
											 .arg(i),this)
								  ,i+1,0,1,1);
		m_lab_ready[i]=new QLabel("not ready",this);
		ui->gridLayout->addWidget(m_lab_ready[i],i+1,1,1,1);
        for(int j=0;j<2;++j)
        {
            m_lcds[i][j]=new QLCDNumber(this);
			ui->gridLayout->addWidget(m_lcds[i][j],i+1,j+2,1,1);
        }
    }
	m_socket=&JSnakeSocket::getInstance();
	connect(m_socket,
			SIGNAL(rcvEnterRoom(JID,JID)),
			SLOT(om_socket_rcvEnterRoom(JID,JID)));
	connect(m_socket,
			SIGNAL(rcvEscapeRoom(JID,JID)),
			SLOT(om_socket_rcvEscapeRoom(JID,JID)));
	connect(m_socket,
			SIGNAL(rcvUserlist(JID,QList<JID>)),
			SLOT(om_socket_rcvUserlist(JID,QList<JID>)));
	connect(m_socket,
			SIGNAL(rcvGA_Ready(bool,int)),
			SLOT(om_socket_rcvGA_Ready(bool,int)));
	connect(m_socket,
			SIGNAL(rcvGA_CountDown(int)),
			SLOT(om_socket_rcvGA_CountDown(int)));
	connect(m_socket,
			SIGNAL(rcvGA_GetCommand()),
			SLOT(om_socket_rcvGA_GetCommand()));
	connect(m_socket,
			SIGNAL(rcvGA_Turn(qint16,int)),
			SLOT(om_socket_rcvGA_Turn(qint16,int)));
	connect(m_socket,
			SIGNAL(rcvGA_Collision(int)),
			SLOT(om_socket_rcvGA_Collision(int)));
	connect(m_socket,
			SIGNAL(rcvGA_CreateBean(QPoint)),
			SLOT(om_socket_rcvGA_CreateBean(QPoint)));
	connect(m_socket,
			SIGNAL(rcvGA_Increase(int)),
			SLOT(om_socket_rcvGA_Increase(int)));
	connect(m_socket,
			SIGNAL(rcvGA_MoveOn(int)),
			SLOT(om_socket_rcvGA_MoveOn(int)));
	connect(m_socket,
			SIGNAL(rcvGA_Stop()),
			SLOT(om_socket_rcvGA_Stop()));
//    QTimer *timer=new QTimer(this);
//    connect(timer,SIGNAL(timeout()),SLOT(moveOn()));
//    timer->start(250);
	setFocus();
	setFocusPolicy(Qt::StrongFocus);
}

JSnakeWidget::~JSnakeWidget()
{
    delete ui;
	delete m_game;
	for(int i=0;i<NUM_SNAKE;++i)
	{
		delete m_lab_ready[i];
		m_lab_ready[i]=NULL;
		for(int j=0;j<2;++j)
		{
			delete m_lcds[i][j];
			m_lcds[i][j]=NULL;
		}
	}
}

void JSnakeWidget::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    painter.drawRect(INITX,INITY,SQUARE_SIZE*MAXX,SQUARE_SIZE*MAXY);
    const static QPixmap pixmaps[NUM_SNAKE+1]={
        tr(":/box/box (0).png"),
        tr(":/box/box (1).png"),
        tr(":/box/box (2).png"),
        tr(":/box/box (3).png"),
        tr(":/box/box (4).png"),
    };
    for(int i=0;i<NUM_SNAKE;++i)
    {
        JSnake::const_iterator it;
        for(it=m_game->getSnakes(i).begin();it != m_game->getSnakes(i).end();++it)
        {
            QRect rect(it.getPoint()*SQUARE_SIZE+QPoint(INITX,INITY),QSize(SQUARE_SIZE,SQUARE_SIZE));
            //painter.drawRect(rect);
            painter.drawPixmap(rect,pixmaps[i]);
        }
    }
    const static QBrush beanbrush(Qt::red);
    painter.setBrush(beanbrush);
    QRect rect(m_game->getBean()*SQUARE_SIZE+QPoint(INITX,INITY),QSize(SQUARE_SIZE,SQUARE_SIZE));
//    painter.drawRect(rect);
    painter.drawPixmap(rect,pixmaps[NUM_SNAKE]);
}

void JSnakeWidget::keyPressEvent(QKeyEvent *key)
{
	qDebug()<<"JSnakeWidget::keyPressEvent"<<key->key();
    switch(key->key())
    {
    case Qt::Key_Up:
		m_command=JSnake::ED_UP;
        break;
    case Qt::Key_Down:
		m_command=JSnake::ED_DOWN;
        break;
    case Qt::Key_Left:
		m_command=JSnake::ED_LEFT;
        break;
    case Qt::Key_Right:
		m_command=JSnake::ED_RIGHT;
		break;
//    case Qt::Key_W:
//        m_game->turn(JSnake::ED_UP,2);
//        break;
//    case Qt::Key_S:
//        m_game->turn(JSnake::ED_DOWN,2);
//        break;
//    case Qt::Key_A:
//        m_game->turn(JSnake::ED_LEFT,2);
//        break;
//    case Qt::Key_D:
//        m_game->turn(JSnake::ED_RIGHT,2);
//        break;

    }
}

//void JSnakeWidget::moveOn()
//{
//    m_game->moveOn();
//    for(int i=0;i<4;++i)
//    {
//        m_lcds[i][0]->display(m_game->getLife(i));;
//        m_lcds[i][1]->display(m_game->getScore(i));;
//    }
//    update();
//}

void JSnakeWidget::om_socket_rcvEnterRoom(JID roomId,JID userId)
{
	if(m_roomId<0)
	{
		if(roomId>0 && userId==JCryproRecorder().getUserId())
		{
			m_roomId=roomId;
			ui->list_players->addItem(QString::number(userId));
		}
	}else{
		if(roomId==m_roomId)
		{
			ui->list_players->addItem(QString::number(userId));
		}
	}
}

void JSnakeWidget::om_socket_rcvEscapeRoom(JID roomId,JID userId)
{
	if(roomId==m_roomId)
	{
		if(userId==JCryproRecorder().getUserId())
		{
			emit escape(0);
		}else{
			QList<QListWidgetItem *>items=ui->list_players->findItems(QString::number(userId),Qt::MatchStartsWith);
			foreach(QListWidgetItem *item,items)
			{
				ui->list_players->removeItemWidget(item);
				delete item;
//				ui->list_players->takeItem(ui->list_players->row(item));
			}
		}
	}
}

void JSnakeWidget::om_socket_rcvUserlist(JID roomId,const QList<JID>& userlist)
{
	if(roomId==m_roomId)
	{
		ui->list_players->clear();
		foreach(JID user,userlist)
		{
			ui->list_players->addItem(QString::number(user));
		}
	}
}

void JSnakeWidget::on_btn_ready_clicked(bool ready)
{
	m_socket->sendGA_Ready(ready);
	if(ready)
	{
		ui->btn_ready->setText(tr("cancel ready"));
		setFocus();
		setFocusPolicy(Qt::StrongFocus);
	}else{
		ui->btn_ready->setText(tr("ready"));
	}
}

void JSnakeWidget::om_socket_rcvGA_Ready(bool ready,int num)
{
	if(num>=0 && num<NUM_SNAKE)
	{
		if(ready)
		{
			m_lab_ready[num]->setText(tr("ready"));
		}else{
			m_lab_ready[num]->setText(tr("not ready"));
		}
	}
}

void JSnakeWidget::on_btn_escape_clicked()
{
	m_socket->sendEscapeRoom();
}

void JSnakeWidget::om_socket_rcvGA_CountDown(int sec)
{
	ui->lab_gamestate->setText(tr("count down : %1").arg(sec));
	if(sec<=1) updateLifeNScore();
	else if(sec>=3){
		m_game->reset();
		updateLifeNScore();
		update();
	}
}

void JSnakeWidget::om_socket_rcvGA_GetCommand()
{
	if(m_command>=0 && m_command < JSnake::ED_NONE)
	{
		m_socket->sendGA_Turn(m_command);
	}
	m_command=JSnake::ED_NONE;
}

void JSnakeWidget::om_socket_rcvGA_Turn(qint16 dire,int num)
{
	m_game->turn(JSnake::EDire(dire),num);
	update();
}

void JSnakeWidget::om_socket_rcvGA_Collision(int num)
{
	m_game->reset(num);
	m_game->decreaseLife(num);
	updateLifeNScore();
}

void JSnakeWidget::om_socket_rcvGA_CreateBean(const QPoint& pt)
{
	m_game->setBean(pt);
	update();
}

void JSnakeWidget::om_socket_rcvGA_Increase(int num)
{
	m_game->increaseScore(num);
	m_game->growLonger(num);
	updateLifeNScore();
}

void JSnakeWidget::om_socket_rcvGA_MoveOn(int num)
{
	m_game->moveOn(num);
	update();
}

void JSnakeWidget::om_socket_rcvGA_Stop()
{
	m_game->reset();
	ui->btn_ready->setChecked(false);
	ui->btn_ready->setText(tr("ready"));
//	updateLifeNScore();
//	update();
}

void JSnakeWidget::updateLifeNScore()
{
	for(int i=0;i<4;++i)
	{
		m_lcds[i][0]->display(m_game->getLife(i));;
		m_lcds[i][1]->display(m_game->getScore(i));;
	}
}
