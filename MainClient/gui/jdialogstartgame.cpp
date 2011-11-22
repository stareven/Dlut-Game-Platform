#include "jdialogstartgame.h"
#include "ui_jdialogstartgame.h"

#include "service/jgameclientloader.h"
#include "pseudoserver/jpseudoserver.h"
#include "service/jdownloader.h"

#include <Global/CodeError>
#include <ClientRequest/JRequestGameInfo>
#include <ClientRequest/JRequestServerInfo>
#include <Socket/JMainClientSocket>

#include <QPushButton>

JDialogStartGame::JDialogStartGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JDialogStartGame)
{
    ui->setupUi(this);
	m_gameClientLoader = new JGameClientLoader;
}

JDialogStartGame::~JDialogStartGame()
{
    delete ui;
	delete m_gameClientLoader;
}

void JDialogStartGame::setGameId(JID gameId)
{
	m_gameId = gameId;
}

int JDialogStartGame::exec()
{
	show();
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	JRequestGameInfo* rgi = new JRequestGameInfo(this);
	JRequestServerInfo* rsi = new JRequestServerInfo(this);
	ui->label->setText(tr("request game info"));
	JGameInfo gi = rgi->pullGameInfo(m_gameId,5*1000);
	ui->label->setText(tr("request server info"));
	JServerInfo si = rsi->pullServerInfo(gi.getServerId(),5*1000);
	ui->label->setText(tr("prepare finished . begin to download"));
	m_gameClientLoader->setParent(parent());
	m_gameClientLoader->setPseudoServer(SHost(QHostAddress::LocalHost,JPseudoServer::getInstance()->serverPort()));
	m_gameClientLoader->setGameInfo(gi);
	m_gameClientLoader->setServerInfo(si);
	m_gameClientLoader->setSession(JMainClientSocket::getInstance()->getSession());
	JDownloader *d = m_gameClientLoader->getDownloader();
	connect(d,
			SIGNAL(begin()),
			SLOT(download_begin()));
	connect(d,
			SIGNAL(rcvTotalSize(qint64)),
			SLOT(download_rcvTotalSize(qint64)));
	connect(d,
			SIGNAL(progress(qint64,qint64)),
			SLOT(download_progress(qint64,qint64)));
	connect(d,
			SIGNAL(finished()),
			SLOT(download_finished()));
	connect(d,
			SIGNAL(error()),
			SLOT(download_error()));
	m_gameClientLoader->download();
	return QDialog::exec();
}

void JDialogStartGame::download_begin()
{
	ui->label->setText(tr("begin to download"));
}

void JDialogStartGame::download_rcvTotalSize(qint64 size)
{
	ui->label->setText(tr("receive total size:%1").arg(size));
}

void JDialogStartGame::download_progress(qint64 a,qint64 b)
{
	int precent = 100*a/b;
	ui->progressBar->setValue(precent);
}

void JDialogStartGame::download_finished()
{
	ui->label->setText(tr("download finished."));
	ui->progressBar->setValue(100);
	m_gameClientLoader->install();
	m_gameClientLoader->start();
	accept();
}

void JDialogStartGame::download_error()
{
	ui->label->setText(tr("error"));
}
