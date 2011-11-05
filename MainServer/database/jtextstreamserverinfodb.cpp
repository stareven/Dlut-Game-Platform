#include "jtextstreamserverinfodb.h"

#include <QFile>
#include <QTextStream>
#include <QMap>

static QMap<JID,JServerInfo> s_serverinfos;

JTextStreamServerInfoDB::JTextStreamServerInfoDB(QObject *parent) :
    JAbstractServerInfoDB(parent)
{
	if(s_serverinfos.isEmpty()){
		QFile file("../database/serverinfo");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream stream(&file);
		for(int i=0;i<1000;++i){
			if(stream.atEnd()) break;
			JID serverId;
			QString name;
			JID runner;
			QString address;
			quint16 port;
			stream>>serverId;
			if(stream.atEnd()) break;
			stream>>name;
			if(stream.atEnd()) break;
			stream>>runner;
			if(stream.atEnd()) break;
			stream>>address;
			if(stream.atEnd()) break;
			stream>>port;
			JServerInfo serverinfo(serverId,name,runner,SHost(QHostAddress(address),port));
			s_serverinfos.insert(serverinfo.getServerId(),serverinfo);
		}
	}
}

JServerInfo JTextStreamServerInfoDB::getServerInfoById(JID id)
{
	return s_serverinfos.value(id,JServerInfo(id,
											  "no such server on server database",
											  -1,
											  SHost()));
}

JCode JTextStreamServerInfoDB::updateServerInfo(const JServerInfo& serverinfo)
{
	s_serverinfos.insert(serverinfo.getServerId(),serverinfo);
	return 0;
}

void JTextStreamServerInfoDB::flush()
{
	if(s_serverinfos.isEmpty()) return;
	QFile file("../database/serverinfo");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);
	foreach(JServerInfo serverinfo,s_serverinfos){
		stream<<serverinfo.getServerId()<<' ';
		stream<<serverinfo.getName()<<' ';
		stream<<serverinfo.getHost().m_address.toString()<<' ';
		stream<<serverinfo.getHost().m_port<<' ';
		stream<<endl;
	}
	s_serverinfos.clear();
}
