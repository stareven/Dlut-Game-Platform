#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShowEvent>
#include <QMessageBox>

#include "service/jrequestgameinfo.h"
#include "service/jdownloadrun.h"
#include "global/ssubserver.h"
#include "service/jrequestuserinfo.h"
#include "service/jrequestport.h"
#include "service/jcryprorecorder.h"

#include "jdlgselectserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gis=new JRequestGameInfo(this);
    m_gis->setObjectName(tr("gameinfosrv"));
	m_currentId=-1;
    ui->setupUi(this);
	m_reqport=new JRequestPort(this);
	SHost hostuserinfo=m_reqport->rqsServerPort(EST_USERINFO);
	m_requserinfo=new JRequestUserInfo(this);
	m_requserinfo->connectToHost(hostuserinfo.m_address,hostuserinfo.m_port);
	m_requserinfo->waitForConnected(1000);
	JCryproRecorder cr;
	m_requserinfo->sendCrypro(cr.getUserId(),cr.getCrypro());
	m_requserinfo->waitForPlh(1000);
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
//	JRequestUserInfo requserinfo;
//	JRequestPort reqpt;
//	SHost hostuserinfo=reqpt.rqsServerPort(EST_USERINFO);
//	requserinfo.connectToHost(hostuserinfo.m_address,hostuserinfo.m_port);
//	requserinfo.waitForConnected(1000);
//	JCryproRecorder cr;
//	requserinfo.sendCrypro(cr.getUserId(),cr.getCrypro());
//	requserinfo.waitForPlh(1000);
	UserInfo::SUserInfo author=m_requserinfo->rqsUserInfo(gi.m_author);
    ui->tb_game->setText(tr("<font color=red>name</font> : %1 <br>"
							"<font color=red>author</font> : %2 %3 %4<br>"
							"<font color=red>version</font> : %5 <br>"
                            "<font color=red>introduction</font> :<br>"
							"%6<br>").arg(gi.m_name)
						 .arg(author.m_userId)
						 .arg(author.m_nickname)
						 .arg(author.m_organization)
						 .arg(gi.m_version.getData())
//                         .arg(gi.m_localVersion.getData())
                         .arg(gi.m_introduction));
	m_gis->rqsServerList(m_currentId,m_gis->getGameInfo(m_currentId).m_version);
}

//void MainWindow::on_btn_get_servers_clicked()
//{
//	m_gis->rqsServerList(m_currentId,m_gis->getGameInfo(m_currentId).m_version);
//}

//void MainWindow::on_btn_download_run_clicked()
//{
//	JDownloadRun dr;
//	SubServer::SGameInfo2 gi=m_gis->getGameInfo(m_currentId);
//	QSet<JID> servers=m_gis->getServerListOnGame(gi.m_gameId);
//	if(servers.empty())
//	{
//		qDebug()<<"server list on game"<<gi.m_gameId<<"is empty.";
//		return;
//	}
//	foreach(JID serverId,servers)
//	{
//		SubServer::SSubServer si=m_gis->getServerInfo(serverId);
//		if( SubServer::SSubServer::ET_GameFileServer ==si.m_type)
//		{
//			dr.start(gi.m_name,gi.m_version,this,si.m_address,si.m_port);
//		}
//	}
//}

void MainWindow::on_btn_start_game_clicked()
{
	if(m_currentId<0)
	{
		QMessageBox::warning(this,
							 tr("no game selected!"),
							 tr("please select a game.")
							 );
		return;
	}
	JDownloadRun dr;
	SubServer::SGameInfo2 gi=m_gis->getGameInfo(m_currentId);
	dr.setGame(gi.m_name,gi.m_version);
	if(dr.needDownload())
	{
		if( QMessageBox::Yes == QMessageBox::question(this,
													  tr("need download"),
													  tr("game file does not exist or version does not match . do you want to download the game client ?"),
													  QMessageBox::Yes | QMessageBox::No
													  )
			){
			qDebug()<<"download";
			QSet<JID> servers=m_gis->getServerListOnGame(gi.m_gameId);
			JDlgSelectServer dlg(this);
			dlg.setText(tr("select server for download"));
			foreach(JID serverId,servers)
			{
				SubServer::SSubServer si=m_gis->getServerInfo(serverId);
				if( SubServer::SSubServer::ET_GameFileServer ==si.m_type)
				{
					dlg.addServer(si);
				}else if(SubServer::SSubServer::ET_GameServer ==si.m_type){
					qDebug()<<"game server::";
					dr.setHost(JDownloadRun::EHT_GameServer,si);
				}
			}
			if(QDialog::Rejected==dlg.exec())
			{
				return;
			}else{
				SubServer::SSubServer si=m_gis->getServerInfo(dlg.getSelectedServer());
				dr.setHost(JDownloadRun::EHT_Download,si);
				if(!dr.download())
				{
					qDebug()<<"download failed";
					return;
				}

			}
		}else{
			qDebug()<<"not download";
		}
	}
	dr.setParent(this);
	QSet<JID> servers=m_gis->getServerListOnGame(gi.m_gameId);
	foreach(JID serverId,servers)
	{
		SubServer::SSubServer si=m_gis->getServerInfo(serverId);
		if(SubServer::SSubServer::ET_GameServer ==si.m_type){
			qDebug()<<"game server::";
			dr.setHost(JDownloadRun::EHT_GameServer,si);
			break;
		}
	}
	dr.setHost(JDownloadRun::EHT_MainServer,m_reqport->getServerPort(EST_FREEPORT));
	if(!dr.run())
	{
		qDebug()<<"run failed";
		return;
	}
}
