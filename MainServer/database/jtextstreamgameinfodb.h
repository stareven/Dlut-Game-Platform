#ifndef JTEXTSTREAMGAMEINFODB_H
#define JTEXTSTREAMGAMEINFODB_H

#include "jabstractgameinfodb.h"

class JTextStreamGameInfoDB : public JAbstractGameInfoDB
{
public:
    explicit JTextStreamGameInfoDB(QObject *parent = 0);
	JGameInfo getGameInfoById(JID id);
	JCode updateGameInfo(const JGameInfo& gameinfo);

	static void flush();
};

#endif // JTEXTSTREAMGAMEINFODB_H
