#include "jhalltalkbroadcaster.h"

JHallTalkBroadcaster::JHallTalkBroadcaster(QObject *parent) :
    QObject(parent)
{
}

JHallTalkBroadcaster* JHallTalkBroadcaster::getInstance()
{
	static JHallTalkBroadcaster* instance = NULL;
	if(NULL == instance){
		static JHallTalkBroadcaster object;
		instance =&object;
	}
	return instance;
}
