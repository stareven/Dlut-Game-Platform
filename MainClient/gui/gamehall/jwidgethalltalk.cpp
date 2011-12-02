#include "jwidgethalltalk.h"
#include "ui_jwidgethalltalk.h"

#include <Processor/JClientHallTalkProcessor>
#include <Socket/JMainClientSocket>
#include <Session/JSession>
#include <ClientRequest/JRequestUserInfo>

JWidgetHallTalk::JWidgetHallTalk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JWidgetHallTalk)
{
	m_processor = JClientHallTalkProcessor::getInstance();
	m_requserinfo = new JRequestUserInfo(this);
    ui->setupUi(this);
	connect(m_processor,SIGNAL(rcvMessage(QString)),SLOT(showMessage(QString)));
	connect(ui->lineEdit,SIGNAL(returnPressed()),SLOT(sendMessageInEdit()));
	connect(ui->pushButton,SIGNAL(clicked()),SLOT(sendMessageInEdit()));
}

JWidgetHallTalk::~JWidgetHallTalk()
{
    delete ui;
}

void JWidgetHallTalk::showMessage(const QString& msg)
{
	ui->textBrowser->append(msg);
}

void JWidgetHallTalk::sendMessageInEdit()
{
	JID myUserID = JMainClientSocket::getInstance()->getSession()->getUserId();
	JUserInfo myUserInfo = m_requserinfo->getUserInfo(myUserID);
	QString msg=tr("%1 says:%2").arg(myUserInfo.getNickname()).arg(ui->lineEdit->text());
	m_processor->sendMessage(msg);
	ui->lineEdit->clear();
}
