#include "jsubserverdb.h"

#include <QMap>
#include <QFile>
#include <QTextStream>

#include "global/ssubserver.h"

static QMap<JID,JID> s_server_runner;
struct SSubServerCheck{
	JID m_serverId;
	QString m_name;
	SubServer::SSubServer::EType m_type;
};
static QMap<JID,SSubServerCheck> s_subservers;

JSubServerDb::JSubServerDb()
{
	static bool first=true;
	if(first)
	{
		first=false;
		{
			QFile file("../database/server_runner");
			file.open(QIODevice::ReadOnly);
			QTextStream stream(&file);
			for(int i=0;i<1000;++i)
			{
				if(stream.atEnd()) break;
				JID serverId,runnerId;
				stream>>serverId>>runnerId;
				s_server_runner.insert(serverId,runnerId);
			}
		}
		{
			QFile file("../database/subserver");
			file.open(QIODevice::ReadOnly);
			QTextStream stream(&file);
			for(int i=0;i<1000;++i)
			{
				if(stream.atEnd()) break;
				SSubServerCheck ssc;
				QString type;
				stream>>ssc.m_serverId>>ssc.m_name>>type;
				if(type=="GS")
				{
					ssc.m_type=SubServer::SSubServer::ET_GameServer;
				}else if(type=="GFS"){
					ssc.m_type=SubServer::SSubServer::ET_GameFileServer;
				}else{
					continue;
				}
				s_subservers.insert(ssc.m_serverId,ssc);
			}
		}
	}
//	if(s_server_runner.isEmpty ())
//	{
//		s_server_runner.insert (53379,902);
//		s_server_runner.insert (53380,902);
//	}
//	if(s_subservers.isEmpty ())
//	{
//		SSubServerCheck sscs[]={
//			{53379,"Multi Snake server",SubServer::SSubServer::ET_GameServer},
//			{53380,"game file server 1",SubServer::SSubServer::ET_GameFileServer},
//		};
//		int NUM_SERVERS=sizeof(sscs)/sizeof(SSubServerCheck);
//		for(int i=0;i<NUM_SERVERS;++i)
//		{
//			s_subservers.insert (sscs[i].m_serverId,sscs[i]);
//		}
//	}
}

bool JSubServerDb::isControlAble(JID serverId,JID runnerId)
{
	if(!s_server_runner.contains (serverId)) return false;
	return s_server_runner[serverId]==runnerId;
}

bool JSubServerDb::checkBaseInfo(const SubServer::SSubServer& ss)
{
	if(!s_subservers.contains (ss.m_serverId)) return false;
	const SSubServerCheck& ssc=s_subservers.value (ss.m_serverId);
	if(ssc.m_serverId!=ss.m_serverId) return false;
	if(ssc.m_name!=ss.m_name) return false;
	if(ssc.m_type!=ss.m_type) return false;
	return true;
}
