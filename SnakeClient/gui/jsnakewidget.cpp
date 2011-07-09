#include "jsnakewidget.h"
#include "ui_jsnakewidget.h"

#include "../SnakeCommon/jsnakegame.h"

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
//    QWidget *gridLayoutWidget;
//    QGridLayout *gridLayout;
//    gridLayoutWidget = new QWidget(this);
//    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
//    gridLayoutWidget->setGeometry(QRect(MAXX*SQUARE_SIZE+INITX+10, 70, 200, 135));
//    gridLayout = new QGridLayout(gridLayoutWidget);
//    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
//    gridLayout->setContentsMargins(0, 0, 0, 0);
	ui->gridLayout->addWidget(new QLabel(tr("life"),this),0,1,1,1);
	ui->gridLayout->addWidget(new QLabel(tr("score"),this),0,2,1,1);
    for(int i=0;i<NUM_SNAKE;++i)
    {
		ui->gridLayout->addWidget(new QLabel(tr("snake%1")
											 .arg(i),this)
								  ,i+1,0,1,1);
        for(int j=0;j<2;++j)
        {
            m_lcds[i][j]=new QLCDNumber(this);
			ui->gridLayout->addWidget(m_lcds[i][j],i+1,j+1,1,1);
        }
    }
	m_socket=&JSnakeSocket::getInstance();
	connect(m_socket,
			SIGNAL(rcvEnterRoom(JID,JID)),
			SLOT(om_socket_rcvEnterRoom(JID,JID)));
	connect(m_socket,
			SIGNAL(rcvUserlist(JID,QList<JID>)),
			SLOT(om_socket_rcvUserlist(JID,QList<JID>)));
//    QTimer *timer=new QTimer(this);
//    connect(timer,SIGNAL(timeout()),SLOT(moveOn()));
//    timer->start(250);
}

JSnakeWidget::~JSnakeWidget()
{
    delete ui;
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
//    qDebug()<<"JSnakeWidget::keyPressEvent";
    switch(key->key())
    {
    case Qt::Key_Up:
        m_game->turn(JSnake::ED_UP,0);
        break;
    case Qt::Key_Down:
        m_game->turn(JSnake::ED_DOWN,0);
        break;
    case Qt::Key_Left:
        m_game->turn(JSnake::ED_LEFT,0);
        break;
    case Qt::Key_Right:
        m_game->turn(JSnake::ED_RIGHT,0);
        break;
    case Qt::Key_W:
        m_game->turn(JSnake::ED_UP,2);
        break;
    case Qt::Key_S:
        m_game->turn(JSnake::ED_DOWN,2);
        break;
    case Qt::Key_A:
        m_game->turn(JSnake::ED_LEFT,2);
        break;
    case Qt::Key_D:
        m_game->turn(JSnake::ED_RIGHT,2);
        break;

    }
}

void JSnakeWidget::moveOn()
{
    m_game->moveOn();
    for(int i=0;i<4;++i)
    {
        m_lcds[i][0]->display(m_game->getLife(i));;
        m_lcds[i][1]->display(m_game->getScore(i));;
    }
    update();
}

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
