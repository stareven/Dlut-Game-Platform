#ifndef JABSTRACTGAMEINFODB_H
#define JABSTRACTGAMEINFODB_H

#include <QObject>

#include <DataStruct/JGameInfo>

class JAbstractGameInfoDB : public QObject
{
    Q_OBJECT
public:
    explicit JAbstractGameInfoDB(QObject *parent = 0);
	virtual JGameInfo getGameInfoById(JID id)=0;
	virtual JCode updateGameInfo(const JGameInfo& gameinfo)=0;
};

#endif // JABSTRACTGAMEINFODB_H
