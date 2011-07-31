#include "service/jrequestlogin.h"

#include <QCoreApplication>

#include "network/jrequestloginsocket.h"
#include "global/elogin.h"
#include "service/jloginhashcoderecorder.h"
#include "global/jelapsedtimer.h"

/*!
	\class JRequestLogin
	\brief 登录请求。

	JRequestLogin对登录请求提供一个基本的封装。
	登录的过程：
	1、通过 JRequestPort 获得登录服务的端口。
	2、调用 connectToHost() 函数连接服务器。
	3、调用 login() 函数发送用户名、密码及登录身份。
*/

/*!
	\fn JRequestLogin::loginResult(bool result)
	\brief 登录结果

	\a result 表示是否登录成功。
	如果登录成功，在发出这个信号前，JRequestLogin 会自动通过 JLoginHashCodeRecorder 记录 userId 及 Login hash code 。
*/

/*!
	构造函数，没啥可说的吧？
*/
JRequestLogin::JRequestLogin(QObject *parent) :
	JRequestBase(parent)
{
    m_socket=new JRequestLoginSocket(this);
	setSocket(m_socket);
	m_state=ELS_Init;
	m_loginError=EL_SUCCESS;
    connect(m_socket,SIGNAL(loginCode(JCode)),SLOT(on_socket_loginCode(JCode)));
}

/*!
	发送登录请求。
	\a loginname 用户名。
	\a passwd 密码。
	\a role 登录身份。

	\sa ERole
*/
void JRequestLogin::login(const QString& loginname,
           const QString& passwd,
           const JID& role)
{
	m_state=ELS_Sending;
    m_socket->login(loginname,passwd,role);
}

/*!
	获取当前的登录状态。

	\sa ELoginState
*/
JRequestLogin::ELoginState JRequestLogin::getLoginState()const
{
    return m_state;
}

/*!
	等待\a msecs 毫秒或收到登录结果。
	\retval true ： 登录成功。
	\retval false ： 登录失败或时间超过\a msecs 毫秒。
*/
bool JRequestLogin::waitForLogined(int msecs)
{
    JElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<msecs)
    {
		if(getLoginState()!=ELS_Sending)
        {
            break;
        }
        QCoreApplication::processEvents();
    }
	return getLoginState()==ELS_Success;
}

/*!
	以可读的文本返回登录错误。
*/
const QString& JRequestLogin::getLoginError()const
{
    static QString noerror="no error";
	if(EL_SUCCESS==m_loginError) return noerror;
	return loginMsg[m_loginError];
}

void JRequestLogin::on_socket_loginCode(JCode code)
{
    switch(code)
	{
    case EL_SUCCESS:
		m_state=ELS_Success;
        {
            JLoginHashCodeRecorder lhcr;
            lhcr.set(m_socket->getCrypro(),m_socket->getUserId());
        }
		emit loginResult(true);
        break;
    default:
		m_state=ELS_Failed;
		m_loginError=(ELogin)code;
		emit loginResult(false);
        break;
    }
}

