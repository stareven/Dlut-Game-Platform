#ifndef JSESSION_H
#define JSESSION_H

#include <QObject>
#include "../global/jglobal.h"

class JSession : public QObject
{
public:
    explicit JSession(QObject *parent = 0);
	JID getUserId()const;
	void setUserId(JID userId);
private:
	JID m_userId;
};

#endif // JSESSION_H
