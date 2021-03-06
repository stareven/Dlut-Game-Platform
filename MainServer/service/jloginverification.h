#ifndef JLOGINVERIFICATION_H
#define JLOGINVERIFICATION_H

#include <QByteArray>

#include "global/jglobal.h"
#include "global/elogin.h"

class QString;

class JLoginVerification
{
public:
    JLoginVerification();

    /// return 0 if succeed , otherwise failed
    ELogin verification(const QString& loginname,const QString& passwd,const JID& role);

    /// return userid if succeed , -1 if failed
    JID getUserId()const;
private:
    JID m_userid;
};

#endif // JLOGINVERIFICATION_H
