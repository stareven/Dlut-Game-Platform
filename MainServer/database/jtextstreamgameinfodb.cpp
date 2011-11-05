#include "jtextstreamgameinfodb.h"

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
		QTextStream stream(&file);
		for(int i=0;i<1000;++i){
			if(stream.atEnd()) break;
			JID gameId;
			QString name;
			quint32 version;
			JID author;
			QString introduction;
			JID serverId;
			QString downloadUrl;
			stream>>gameId;
			if(stream.atEnd()) break;
			stream>>name;
			if(stream.atEnd()) break;
			stream>>version;
			if(stream.atEnd()) break;
			stream>>author;
			if(stream.atEnd()) break;
			stream>>introduction;
			if(stream.atEnd()) break;
			stream>>serverId;
			if(stream.atEnd()) break;
			stream>>downloadUrl;
			JGameInfo gameinfo(gameId,
							   name,
							   JVersion(version),
							   author,
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
		stream<<gameinfo.getGameId()<<' ';
		stream<<gameinfo.getName()<<' ';
		stream<<gameinfo.getVersion().getData()<<' ';
		stream<<gameinfo.getAuthor()<<' ';
		stream<<gameinfo.getIntroduction()<<' ';
		stream<<gameinfo.getServerId()<<' ';
		stream<<gameinfo.getDownloadUrl().toString();
		stream<<endl;
	}
	s_gameinfos.clear();
}
