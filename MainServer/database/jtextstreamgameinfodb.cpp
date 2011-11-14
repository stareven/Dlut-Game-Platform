#include "jtextstreamgameinfodb.h"

#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMap>

static QMap<JID,JGameInfo> s_gameinfos;

JTextStreamGameInfoDB::JTextStreamGameInfoDB(QObject *parent) :
    JAbstractGameInfoDB(parent)
{
	if(s_gameinfos.isEmpty()){
		QFile file("../database/gameinfo");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		for(int i=0;i<1000;++i){
			if(file.atEnd()) break;
			QString strLine = file.readLine(500);
			QStringList split = strLine.split(QRegExp("#|\n"));
			if(split.length()<8){
				continue;
			}
			JID gameId=split.at(0).toInt();
			QString name=split.at(1);
			quint32 version=split.at(2).toInt();
			JID author=split.at(3).toInt();
			JID runner=split.at(4).toInt();
			QString introduction=split.at(5);
			JID serverId=split.at(6).toInt();
			QString downloadUrl=split.at(7);
			JGameInfo gameinfo(gameId,
							   name,
							   JVersion(version),
							   author,
							   runner,
							   introduction,
							   serverId,
							   QUrl(downloadUrl));
			s_gameinfos.insert(gameinfo.getGameId(),gameinfo);
		}
	}
}

JGameInfo JTextStreamGameInfoDB::getGameInfoById(JID id)
{
	return s_gameinfos.value(id,
							 JGameInfo(id,
										"no such game on server database",
										JVersion(1),
										-1,
										-1,
										"no such game on server database",
										-1,
										QUrl()));
}

JGameList JTextStreamGameInfoDB::getGameList()
{
	JGameList gl;
	foreach(const JGameInfo& gi,s_gameinfos){
		gl.insert(gi.getGameId(),gi.getName());
	}
	return gl;
}

JCode JTextStreamGameInfoDB::updateGameInfo(const JGameInfo& gameinfo)
{
	s_gameinfos.insert(gameinfo.getGameId(),gameinfo);
	return 0;
}

void JTextStreamGameInfoDB::flush()
{
	if(s_gameinfos.isEmpty()) return;
	QFile file("../database/gameinfo");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream stream(&file);
	foreach(JGameInfo gameinfo,s_gameinfos){
		stream<<gameinfo.getGameId()<<'#';
		stream<<gameinfo.getName()<<'#';
		stream<<gameinfo.getVersion().getData()<<'#';
		stream<<gameinfo.getAuthor()<<'#';
		stream<<gameinfo.getRunner()<<'#';
		stream<<gameinfo.getIntroduction()<<'#';
		stream<<gameinfo.getServerId()<<'#';
		stream<<gameinfo.getDownloadUrl().toString();
		stream<<endl;
	}
	s_gameinfos.clear();
}
