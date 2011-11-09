#ifndef JCLIENTSESSION_H
#define JCLIENTSESSION_H

#include "jsession.h"

class JClientSession : public JSession
{
	explicit JClientSession(QObject *parent);
public:
	static JClientSession* getInstance();
};

#endif // JCLIENTSESSION_H
