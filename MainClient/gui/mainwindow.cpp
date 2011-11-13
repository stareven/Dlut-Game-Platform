#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShowEvent>
#include <QMessageBox>
#include <QPalette>

#include "service/jdownloadrun.h"

#include <ClientRequest/JRequestGameInfo>
#include <ClientRequest/JRequestUserInfo>
#include <Socket/JMainClientSocket>
#include <Session/JSession>

#include "jdlgselectserver.h"
#include "widgetadmin/jwidgetadmin.h"
#include "dialogupdateuserinfo/jdialogupdateuserinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gis=new JRequestGameInfo(this);
    m_gis->setObjectName(tr("gameinfosrv"));
	m_currentId=-1;
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);
    palette.setColor(QPalette::Base, QColor(0,0,0));
    palette.setColor(QPalette::Text, QColor(Qt::green));
    palette.setColor(QPalette::HighlightedText, QColor(Qt::red));
    ui->list_game->setPalette(palette);
    ui->tb_game->setPalette(palette);

	m_requserinfo=new JRequestUserInfo(this);
	m_widgetadmin=NULL;
	connect(JMainClientSocket::getInstance(),
			SIGNAL(disconnected()),
			SLOT(On_socket_disconnected()));
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
    on_btn_refresh_list_clicked();
	on_btn_refresh_myuserinfo_clicked();
}

void MainWindow::on_actionShow_admin_window_triggered()
{
	if(m_widgetadmin==NULL){
		m_widgetadmin=new JWidgetAdmin(this);
		m_widgetadmin->setWindowFlags(Qt::Window);
	}
	m_widgetadmin->show();
}

void MainWindow::on_btn_refresh_list_clicked()
{
    ui->list_game->clear();
    ui->tb_game->clear();
	m_currentId=-1;
	updateGameList();
}

void MainWindow::On_socket_disconnected()
{
	QMessageBox::critical(this,
						  tr("network disconnected"),
						  tr("network disconnected."));
}

void MainWindow::on_list_game_itemClicked(QListWidgetItem* item)
{
	JGameList gl = m_gis->pullGameList(1000);
	foreach(const QString& name,gl)
    {
		if(item->text()==name)
        {
			m_currentId=gl.key(name);
            break;
        }
	}
	updateGameInfo(m_currentId);
}

void MainWindow::updateGameList()
{
	JGameList gl = m_gis->pullGameList(1000);
	foreach(const QString& name,gl)
	{
		ui->list_game->addItem(name);
	}
}

void MainWindow::updateGameInfo(JID gameId)
{
	JGameInfo gi=m_gis->pullGameInfo(gameId);
	JUserInfo author=m_requserinfo->pullUserInfo(gi.getAuthor());
	ui->tb_game->setText(tr("<font color=red>name</font> : %1 <br>"
							"<font color=red>author</font> : %2 %3 %4<br>"
							"<font color=red>version</font> : %5 <br>"
							"<font color=red>introduction</font> :<br>"
							"%6<br>").arg(gi.getName())
						 .arg(author.getUserId())
						 .arg(author.getNickname())
						 .arg(author.getOrganization())
						 .arg(gi.getVersion().getData())
						 .arg(gi.getIntroduction()));
}

void MainWindow::on_btn_start_game_clicked()
{/*
	if(m_currentId<0)
	{
		QMessageBox::warning(this,
							 tr("no game selected!"),
							 tr("please select a game.")
							 );
		return;
	}
	JDownloadRun dr;
	JGameInfo gi=m_gis->pullGameInfo(m_currentId);
	dr.setGame(gi.getName(),gi.getVersion());
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
			return;
		}
	}
	dr.setParent(this);
	QSet<JID> servers=m_gis->getServerListOnGame(gi.m_gameId);
	foreach(JID serverId,servers)
	{
		SubServer::SSubServer si=m_gis->getServerInfo(serverId);
		if(SubServer::SSubServer::ET_GameServer ==si.m_type){
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
	//*/
}

void MainWindow::on_btn_refresh_myuserinfo_clicked()
{
	JID myUserID = JMainClientSocket::getInstance()->getSession()->getUserId();
	m_myUserInfo = m_requserinfo->pullUserInfo(myUserID);
	ui->text_userid->setText(QString::number(m_myUserInfo.getUserId()));
	ui->text_nickname->setText(m_myUserInfo.getNickname());
	ui->text_organization->setText(m_myUserInfo.getOrganization());
}

void MainWindow::on_btn_update_myuserinfo_clicked()
{
	JDialogUpdateUserInfo dlg(this);
	dlg.setInitUserInfo(m_myUserInfo);
	if(QDialog::Accepted == dlg.exec()){
		on_btn_refresh_myuserinfo_clicked();
	}
}
