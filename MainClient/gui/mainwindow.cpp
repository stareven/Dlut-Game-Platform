#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShowEvent>
//#include <QDebug>

#include "service/jgameinfoservice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gis=new JGameInfoService(this);
    m_gis->setObjectName(tr("gameinfosrv"));
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
    m_gis->rqsNameList();
}

void MainWindow::on_gameinfosrv_nameListReady()
{
    foreach(SGameName gn,m_gis->getNameList())
    {
        ui->list_game->addItem(gn.m_name);
    }
}

void MainWindow::on_list_game_itemClicked(QListWidgetItem* item)
{
    foreach(SGameName gn,m_gis->getNameList())
    {
        if(item->text()==gn.m_name)
        {
            m_gis->rqsGameInfo(gn.m_gameId);
            break;
        }
    }
}

void MainWindow::on_gameinfosrv_gameInfoReady(JID gameid)
{
    SGameInfo gi=m_gis->getGameInfo(gameid);
    ui->tb_game->setText(tr("<font color=red>name</font> : %1 <br>"
                            "<font color=red>author</font> : %2 <br>"
                            "<font color=red>server version</font> : %3 <br>"
                            "<font color=red>local version</font> : %4 <br>"
                            "<font color=red>introduction</font> :<br>"
                            "%5<br>").arg(gi.m_name)
                         .arg(gi.m_author)
                         .arg(gi.m_serverVersion.getData())
                         .arg(gi.m_localVersion.getData())
                         .arg(gi.m_introduction));
}
