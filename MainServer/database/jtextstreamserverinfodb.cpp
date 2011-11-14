#include "jtextstreamserverinfodb.h"

#include <QStringList>
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
		for(int i=0;i<1000;++i){
			if(file.atEnd()) break;
			QString strLine = file.readLine(500);
			QStringList split = strLine.split(QRegExp("#|\n"));
			if(split.length()<5){
				continue;
			}
			JID serverId=split.at(0).toInt();
			QString name=split.at(1);
			JID runner=split.at(2).toInt();
			QString address = split.at(3);
			quint16 port=split.at(4).toInt();
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
		stream<<serverinfo.getServerId()<<'#';
		stream<<serverinfo.getName()<<'#';
		stream<<serverinfo.getRunner()<<'#';
		stream<<serverinfo.getHost().m_address.toString()<<'#';
		stream<<serverinfo.getHost().m_port;
		stream<<endl;
	}
	s_serverinfos.clear();
}
