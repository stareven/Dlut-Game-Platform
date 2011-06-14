#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShowEvent>
//#include <QDebug>

#include "service/jgameinfoservice.h"
#include "ssubserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gis=new JGameInfoService(this);
    m_gis->setObjectName(tr("gameinfosrv"));
	m_currentId=-1;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::showEvent ( QShowEvent * event)
{
    QMainWindow::showEvent(event);
    //qDebug()<<"MainWindow::showEvent";
    on_btn_refresh_list_clicked();
}

void MainWindow::on_btn_refresh_list_clicked()
{
    ui->list_game->clear();
    ui->tb_game->clear();
	m_currentId=-1;
	m_gis->rqsGameList();
}

void MainWindow::on_gameinfosrv_gameListReady()
{
	foreach(SubServer::SGameInfo2 gn,m_gis->getGames())
    {
        ui->list_game->addItem(gn.m_name);
    }
}

void MainWindow::on_list_game_itemClicked(QListWidgetItem* item)
{
	foreach(SubServer::SGameInfo2 gn,m_gis->getGames())
    {
        if(item->text()==gn.m_name)
        {
			m_currentId=gn.m_gameId;
			//m_gis->rqsGameInfo(gn.m_gameId);
            break;
        }
    }
	m_gis->rqsGameInfo(m_currentId);
}

void MainWindow::on_gameinfosrv_gameInfoReady(JID gameid)
{
	SubServer::SGameInfo2 gi=m_gis->getGameInfo(gameid);
    ui->tb_game->setText(tr("<font color=red>name</font> : %1 <br>"
                            "<font color=red>author</font> : %2 <br>"
							"<font color=red>version</font> : %3 <br>"
                            "<font color=red>introduction</font> :<br>"
							"%4<br>").arg(gi.m_name)
                         .arg(gi.m_author)
						 .arg(gi.m_version.getData())
//                         .arg(gi.m_localVersion.getData())
                         .arg(gi.m_introduction));
}

void MainWindow::on_btn_get_servers_clicked()
{
	m_gis->rqsServers(m_currentId,m_gis->getGameInfo(m_currentId).m_version);
}
