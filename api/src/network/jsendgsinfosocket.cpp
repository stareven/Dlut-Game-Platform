#include "network/jsendgsinfosocket.h"

#include "global/ssubserver.h"

/*!
	\defgroup subserver subserverapi
	\brief 处理 SubServer 向 MainServer 发送数据
*/

/*!
	\file jsendgsinfosocket.h
	\brief 定义了 JSendGsInfoSocket 类
*/

/*!
	\class JSendGsInfoSocket jsendgsinfosocket.h "network/jsendgsinfosocket.h"
	\ingroup subserver
	\brief 封装发送游戏信息的底层通信
	
	SubServer 需要向 MainServer 发送服务器信息、游戏信息及关联信息。
	
	\note DGP API 提供了更加易于使用的 JSendGsInfo 类来处理发送游戏信息请求。
	
	\section sendgsinfo_protocol 通信协议
	首先，这个通信协议只定义了\ref lhc_protocol "LoginHashConfirm通信协议" 中data的部分。\n
	查看完整的通信协议，请见\ref lhc_protocol "LoginHashConfirm通信协议" 。\n
	
	- 客户端向服务器端发送服务器信息 : <JID:protocol> <SubServer::SSubServer:subserverinfo>
	  -# ::JID 类型，值为 SubServer::ESP_ServerInfo，表示发送协议为发送服务器信息。
	  -# SubServer::SSubServer ，表示服务器信息。格式化方式参见 ::operator<<(QDataStream& stream,const SubServer::SSubServer& )
	- 客户端向服务器端发送游戏信息 : <JID:protocol> <SubServer::SGameInfo2:gameinfo>
	  -# ::JID 类型，值为 SubServer::ESP_GameInfo，表示发送协议为发送游戏信息。
	  -# SubServer::SGameInfo2 ，表示游戏信息。格式化方式参见 ::operator<<(QDataStream& stream,const SubServer::SGameInfo2& )
	- 客户端向服务器端发送服务器信息 : <JID:protocol> <JID:serverId> <JID:gameId> <JVersion:gameVersion>
	  -# ::JID 类型，值为 SubServer::ESP_Relation，表示发送协议为发送关联信息。
	  -# ::JID 类型，表示服务器ID。
	  -# ::JID 类型，表示游戏ID。
	  -# ::JVersion 类型，表示游戏版本。格式化方式参见 operator<<(QDataStream& ,const JVersion& )
	- 服务器端向客户端 ： <JID:protocol> <JCode:code>
	  -# ::JID 类型，表示发送协议。
	  -# ::JCode 类型，0表示发送成功。其它表示各种原因的失败。（有空把这个地方详细写一下。）
	
	\sa JSendGsInfo
*/

/*!
	\fn JSendGsInfoSocket::rcvSendCode(JID protocol,JCode code)
	\brief 收到发送的返回码
	
	\a protocol 表示发送协议。参见 SubServer::ESubServerProtocol 。\n
	\a code 表示发送结果。0表示发送成功。其它表示各种原因的失败。（有空把这个地方详细写一下。）
*/

/*!
	\brief 构造函数
	
	这个构造函数我就不写了啊。
*/
JSendGsInfoSocket::JSendGsInfoSocket(QObject *parent) :
	JLhcSocketBase(parent)
{
}

/*!
	\brief 发送服务器信息
	
	\a ss 表示服务器信息。
	
	\sa SubServer::SSubServer
*/
void JSendGsInfoSocket::sendServerInfo(const SubServer::SSubServer& ss)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::ESP_ServerInfo;
	outstream<<ss;
	sendData(outdata);
}

/*!
	\brief 发送游戏信息
	
	\a gi 表示游戏信息。
	
	\sa SubServer::SGameInfo2
*/
void JSendGsInfoSocket::sendGameInfo(const SubServer::SGameInfo2& gi)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::ESP_GameInfo;
	outstream<<gi;
	sendData(outdata);
}

/*!
	\brief 发送关联信息
	
	\a serverId 表示服务器ID，\a gameId 表示游戏ID，\a gameVersion 表示游戏版本。
	
	关联信息表示服务器\a serverId 为\a gameId 的\a gameVersion 版本的游戏提供服务。
*/
void JSendGsInfoSocket::sendRelation(JID serverId,
								 JID gameId,
								 const JVersion& gameVersion)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)SubServer::ESP_Relation;
	outstream<<serverId<<gameId<<gameVersion;
	sendData(outdata);
}

void JSendGsInfoSocket::afterLhc(const QByteArray& data)
{
    QDataStream stream(data);
	JID protocol;
    stream>>protocol;
	switch((SubServer::ESubServerProtocol)protocol)
    {
	case SubServer::ESP_ServerInfo:
	case SubServer::ESP_GameInfo:
	case SubServer::ESP_Relation:
		{
			JCode code;
			stream>>code;
			emit rcvSendCode (protocol,code);
		}
		break;
	case SubServer::ESP_Command:
		{
			qDebug()<<"JSubServerConnection::dataProcess : undefined protocol.";
		}
		break;
    }
}

