#ifndef JCRYPRORECORDER_H
#define JCRYPRORECORDER_H

#include <QByteArray>

#include "global/jglobal.h"

#include "clientapi_global.h"

class CLIENTAPISHARED_EXPORT JCryproRecorder
{
public:
    JCryproRecorder();
    void set(const QByteArray&,JID);
    void setCrypro(const QByteArray&);
    const QByteArray& getCrypro()const;
    void setUserId(JID id);
    JID getUserId()const;
private:
    static QByteArray s_crypro;
    static JID s_userid;
};

#endif // JCRYPRORECORDER_H
