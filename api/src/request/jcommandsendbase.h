#ifndef JCOMMANDSENDBASE_H
#define JCOMMANDSENDBASE_H

#include "jrequestbase.h"

class JClientCommandProcessor;

class JCommandSendBase : public JRequestBase
{
    Q_OBJECT
public:
    explicit JCommandSendBase(QObject *parent = 0);
	void sendShutdown();
	void sendRestart();
private:
	JClientCommandProcessor* m_processor;
};

#endif // JCOMMANDSENDBASE_H
