#ifndef JSNAKEGLOBAL_H
#define JSNAKEGLOBAL_H

#include <QList>

#include "global/jglobal.h"

class QDataStream;
namespace Snake{
	class JRoom;
}
QDataStream& operator>>(QDataStream& ,Snake::JRoom&);
QDataStream& operator<<(QDataStream& ,const Snake::JRoom&);
namespace Snake{
	const int Max_Players=4;
	class JRoom{
	public:
		JRoom(const QString& roomName=QString(),JID roomId=-1)
		{
			m_roomName=roomName;
			m_roomId=roomId;
			for(int i=0;i<Max_Players;++i)
			{
				m_players[i]=-1;
			}
		}
		JID getRoomId()const
		{
			return m_roomId;
		}
		void setRoomId(JID roomId)
		{
			m_roomId=roomId;
		}
		const QString& getRoomName()const
		{
			return m_roomName;
		}
		int getPlayersCount()const
		{
			int ret=0;
			for(int i=0;i<Max_Players;++i)
			{
				if(m_players[i]>=0) ++ret;
			}
			return ret;
		}
		bool isEmpty()const
		{
			return getPlayersCount()<=0;
		}
		bool isFull()const
		{
			return getPlayersCount()>=Max_Players;
		}
		bool enterRoom(JID userId)
		{
			for(int i=0;i<Max_Players;++i)
			{
				if(m_players[i]<0)
				{
					m_players[i]=userId;
					return true;
				}
			}
			return false;
		}
		bool leaveRoom(JID userId)
		{
			for(int i=0;i<Max_Players;++i)
			{
				if(m_players[i]==userId)
				{
					m_players[i]=-1;
					return true;
				}
			}
			return false;
		}
		JID getPlayer(int num)const
		{
			if(num<0 || num>=Max_Players)
				return -1;
			return m_players[num];
		}
		int getPositionById(JID userId)const
		{
			for(int i=0;i<Max_Players;++i)
			{
				if(m_players[i]==userId)
				{
					return i;
				}
			}
			return -1;
		}
	private:
		JID m_roomId;
		QString m_roomName;
		JID m_players[Max_Players];
	public:
		friend QDataStream& ::operator>>(QDataStream& ,JRoom&);
		friend QDataStream& ::operator<<(QDataStream& ,const JRoom&);
	};
}

namespace SnakeProtocol{
	typedef quint16 JProtocol;
	const JProtocol SP_Hello = 0x1000;
		// C -> S : SP_Hello , <JID>userid ,
		// S -> C : SP_Hello , <JCode>code ,
	const JProtocol SP_Roomlist = 0x2000;
		// C -> S : SP_Roomlist ,
		// S -> C : SP_Roomlist , < QList<JRoom> >roomlist ,
	const JProtocol SP_RoominfoUpdate = ( SP_Roomlist | 0x0100 );
		// C -> S : SP_RoominfoUpdate , <JID>roomid
			// 0是大厅
		// S -> C : SP_RoominfoUpdate , <JRoom>roominfo ,
			// 这可以单独发送，比如Server端房间列表有更新的时候。
	const JProtocol SP_RoominfoAdd = ( SP_Roomlist | 0x0200 );
		// C -> S : SP_RoominfoAdd , <JRoom>roominfo ,
			// 新建房间
		// S -> C : SP_RoominfoAdd , <JRoom>roominfo ,
	const JProtocol SP_RoominfoDelete = ( SP_Roomlist | 0x0300 );
		// S -> C : SP_RoominfoDelete , <JID>roomid ,
		// C -> S : SP_RoominfoDelete , <JID>roomid ,
	const JProtocol SP_RoomAct = 0x3000;
	const JProtocol SP_RoomEnter = ( SP_RoomAct | 0x0100 );
		// C -> S : SP_Roomenter , <JID>roomid ,
		// S -> C : SP_Roomenter , <JID>roomid , <JID>userid ,
			//这个得发给所有人，因为m_nPlayer被删掉。
	const JProtocol SP_RoomEscape = ( SP_RoomAct | 0x0200 );
		// C -> S : SP_Roomescape
		// C -> S : SP_Roomescape , <JID>fromroomid , <JID>userid , <JCode>result ,
			//这个得发给所有人，因为m_nPlayer被删掉。
	const JProtocol SP_Userlist = 0x4000;
		// C -> S : SP_Userlist ,
		// S -> C : SP_Userlist , <JID>roomid , <QList<JID> >userlist ,
	const JProtocol SP_GameInfo = 0x5000;
	const JProtocol SP_GI_UseridList = ( SP_GameInfo | 0x0100 );
		// C -> S : SP_GI_UseridList
		// S -> C : SP_GI_UseridList , <QList<JID> >useridlist
	const JProtocol SP_GI_Ready = ( SP_GameInfo | 0x0200 );
		// C -> S : SP_GI_Ready , <bool>ready
			// true : ready ; false : cancel ready
		// C -> S : SP_GI_Ready , <bool>ready , <JID>userid
	const JProtocol SP_GameAct = 0x6000;
	const JProtocol SP_GA_CountDown = ( SP_GameAct | 0x0100 );
		// S -> C : SP_GA_CountDown , <int>n
	const JProtocol SP_GA_GetCommand = ( SP_GameAct | 0x0200 );
		// S -> C : SP_GA_GetCommand
	const JProtocol SP_GA_Turn = ( SP_GameAct | 0x0300 );
		// C -> S : SP_GA_Turn , <JSnake::EDire>dire
		// S -> C : SP_GA_Turn , <JSnake::EDire>dire , <JID>userid
	const JProtocol SP_GA_Collision = ( SP_GameAct | 0x0400 );
		// S -> C : SP_GA_Collision , <JID>userid
	const JProtocol SP_GA_CreateBean = ( SP_GameAct | 0x0500 );
		// S -> C : SP_GA_CreateBean , <QPoint>pt
	const JProtocol SP_GA_IncreaseScore = ( SP_GameAct | 0x0600 );
		// S -> C : SP_GA_IncreaseScore , <JID>userid
	const JProtocol SP_GA_MoveOn = ( SP_GameAct | 0x0700 );
		// S -> C : SP_GA_MoveOn , <JID>userid
}
#endif // JSNAKEGLOBAL_H
